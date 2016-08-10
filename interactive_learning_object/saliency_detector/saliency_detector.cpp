/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-20 v1
*/
#include "saliency_detector.h"

using std::string;
using std::cout;
using std::endl;
using cv::Mat;

namespace learn_obj {
  
int SaliencyDetector::MaxMat(const Mat& mat) {
  int width = mat.rows;
  int height = mat.cols;
  uint16_t max;
  for (int i = 0; i < width; ++i)
  { //[shenli] open curly brace should be end of above line
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

void SaliencyDetector::ConvertTo8U(Mat& mat) {
  // int max = MaxMat(mat);
  int width = mat.rows;
  int height = mat.cols;
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      mat.at<uint16_t>(i,j) = mat.at<uint16_t>(i,j)*(1.0/65535)*255.0;
    }
  }
}

void SaliencyDetector::EachDepthPixelNum(const Mat& mat, int* vec) {
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

int SaliencyDetector::FindBestOFFSET(int* vec, int offset) {
  int max_i;
  int max_sum=0;
  for (int i = 1; i < 256-offset; ++i) {
    int sum = 0;
    for (int j = 0; j < offset; ++j) {
      sum = vec[i+j];
    }
    if (sum > max_sum) {
      max_sum = sum;
      max_i = i;
    }
  }
  return max_i;
}

cv::Rect SaliencyDetector::Detect(const cv::Mat& rgb_image, const cv::Mat& depth_image) {

	cv::Mat depth_image_uint8 = depth_image;
  if (MaxMat(depth_image) > 255)
    ConvertTo8U(depth_image_uint8);
  
  int depth_pixel_num[256] = {0};
  EachDepthPixelNum(depth_image_uint8, depth_pixel_num);

  int max_n = FindBestOFFSET(depth_pixel_num, koffset);
     
  // Checks if array elements lie between the elements of two other arrays
  Mat mask;
  cv::inRange(depth_image_uint8, max_n, max_n+koffset-1, mask);

  // MedianBlur to filter the noise, it outperforms the dstImg 
  Mat dst_image = mask.clone();

  // GaussianBlur(depthImg, dstImg, Size(5,5), 0, 0);
  cv::medianBlur(mask, dst_image, 5);

  // find contours from the image
  std::vector<std::vector<cv::Point>> contours;
  cv::findContours(dst_image, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
  // find the largest area
  Mat area(1,contours.size(),CV_32FC1);
  float max_area = area.at<float>(0);
  int max_i=0;
  for (int i = 0; i < contours.size(); ++i)
  {
    area.at<float>(i) = cv::contourArea(contours[i]);
    if (max_area < area.at<float>(i))
    {
      max_area = area.at<float>(i);
      max_i = i;
    }
  }

  cv::Rect saliency_rect_ = cv::boundingRect(contours[max_i]);
  return saliency_rect_;
}}