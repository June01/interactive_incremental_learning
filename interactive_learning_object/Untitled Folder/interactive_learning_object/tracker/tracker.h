/*
	Author: June Xie
	E-mail: ttxie@mobvoi.com
	Date: 2016-05-24
*/
#ifndef LEARNINGOBJECT_TRACKER_TRACKER_H
#define LEARNINGOBJECT_TRACKER_TRACKER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <dlib/opencv.h>
#include <dlib/image_processing.h>

#include "learn_obj.hpp"
/*
	Function: Tracker is used to tracking an image.
	Dependency: dlib opencv
	Input: gray image and initial bounding box of the first image
	Output: bouding box of the image
*/
namespace learn_obj {
class Tracker {

 public:
  // Initialize the tracker with the first image and saliency bounding box
  // Tracker();
  void TrackerInit(const cv::Mat& image, const cv::Rect& rect);
  // Tracking an image and return an cv::Rect
  cv::Rect Tracking(const cv::Mat& image);

 private:
  dlib::correlation_tracker tracker;

};
}

#endif //LEARNINGOBJECT_TRACKER_TRACKER_H
