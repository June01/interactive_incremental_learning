/*
 ** Author: June Xie
 ** E-mail: ttxie@mobvoi.com
 ** Date: 2016-05-20 v1
 */
#ifndef LEARNINGOBJECT_SALIENCYDETECTOR_SALIENCYDETECTOR_H
#define LEARNINGOBJECT_SALIENCYDETECTOR_SALIENCYDETECTOR_H
#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

/*
 ** Function: SaliencyDetectionDepth is used to detect saliency from depth img and return a Rect.
 ** Dependency: OpenCV
 ** Input: The rgb and depth version of the same image in Mat format(OpenCV)
 ** Output: The saliency area in Rect format(OpenCV) 
 */
namespace learn_obj {

class SaliencyDetector {

 public:
  // Constructor: class initialized  
  // SaliencyDetectorDepth();
  // Detect the saliency Rect
  cv::Rect Detect(const cv::Mat& rgb_image, const cv::Mat& depth_image);
  private:
  // If it is devided by MaxMat, 3 will be better, other else 65535
  static const int koffset = 1;
  // Find the biggest element of mat 
  int MaxMat(const cv::Mat& mat);
  // Turn Mat uint16_t to uint8_t 
  void ConvertTo8U(cv::Mat& mat);
  // Count the pixel num of each Depth 
  void EachDepthPixelNum(const cv::Mat& mat, int* vec);
  // Find the most depth, OFFSET the most several nearest depth, not the only one  
  int FindBestOFFSET(int* vec, int offset);
  
};}
#endif //LEARNINGOBJECT_SALIENCYDETECTOR_SALIENCYDETECTOR_H
