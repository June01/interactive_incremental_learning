/*
	Author: June Xie
	E-mail: ttxie@mobvoi.com
	Date: 2016-05-20 v1
*/
#include "SaliencyDetectionDepth.h"

SaliencyDetectionDepth::SaliencyDetectionDepth(Mat rgbImage, Mat depthImage) {
	rgbImg = rgbImage;
	depthImg = depthImage;
	cout << "This is the constructor" << endl;
}

int SaliencyDetectionDepth::maxMat(Mat mat)
{//[shenli] do not put open curly brace on the start of next line
	int width = mat.rows;
	int height = mat.cols;
	uint16_t max;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			if (max < mat.at<uint16_t>(i,j))
			{
				max = mat.at<uint16_t>(i,j);
			}
		}
	}
	return static_cast<int>(max);
}

void SaliencyDetectionDepth::convertTo8U(Mat& mat)
{
	int max = maxMat(mat);
	int width = mat.rows;
	int height = mat.cols;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			mat.at<uint16_t>(i,j) = mat.at<uint16_t>(i,j)*(1.0/max)*255.0;
		}
	}
}

void SaliencyDetectionDepth::eachDepthPixelNum(Mat mat, int* vec)
{
	int width = mat.rows;
	int height = mat.cols;
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
		{
			int k = int(mat.at<uint16_t>(i,j));
			vec[k]++;
		}
	}
}

int SaliencyDetectionDepth::findBestOFFSET(int* vec, int offset)
{
	int maxI;
	int maxSum=0;
	for (int i = 1; i < 256-offset; ++i)
	{
		int sum = 0;
		for (int j = 0; j < offset; ++j)
		{
			sum = vec[i+j];
		}
		if (sum > maxSum)
		{
			maxSum = sum;
			maxI = i;
		}
	}
	return maxI;
}

Rect SaliencyDetectionDepth::saliencyRectDetection()
{
	// For the convenient saliency depth computation, we turn the 16bit depth image to 8bit
 	convertTo8U(depthImg); 	
 
 	int depthPixelNum[256] = {0};
 	eachDepthPixelNum(depthImg, depthPixelNum);

 	int maxN = findBestOFFSET(depthPixelNum, OFFSET);
 	 	
 	// Checks if array elements lie between the elements of two other arrays
 	Mat mask;
 	inRange(depthImg, maxN, maxN+OFFSET-1, mask);

    // MedianBlur to filter the noise, it outperforms the dstImg 
 	Mat dstImg = mask.clone();

	// GaussianBlur(depthImg, dstImg, Size(5,5), 0, 0);
 	medianBlur(mask, dstImg, 5);

 	// find contours from the image
 	std::vector<std::vector<Point>> contours;
 	findContours(dstImg, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
 	// find the largest area
 	Mat area(1,contours.size(),CV_32FC1);
 	float maxArea = area.at<float>(0);
 	int maxI=0;
 	for (int i = 0; i < contours.size(); ++i)
 	{
 		area.at<float>(i) = contourArea(contours[i]);
 		if (maxArea < area.at<float>(i))
 		{
 			maxArea = area.at<float>(i);
 			maxI = i;
 		}
 	}

 	cnt = boundingRect(contours[maxI]);
 	return cnt;
}
