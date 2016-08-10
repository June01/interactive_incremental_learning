/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-24
*/
#ifndef LEARNINGOBJECT_DETECTOR_DETECTOR_H
#define LEARNINGOBJECT_DETECTOR_DETECTOR_H
#include <opencv2/core/core.hpp>

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>

#include "learn_obj.hpp"
/*
  Function: Detector is used to detect an image.
  Dependency: dlib opencv
  Input: detector and image to be detect 
  Output: bouding boxes of the image
*/
namespace learn_obj {
class Detector {
 public:
  // Input the dlib image and return dlib::rectangle
  std::vector<dlib::rectangle> Detecting(
    const dlib::array2d<unsigned char>& a2d_image,
    dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >>& detector);
  // Input the OpenCV image and return cv::Rect
  std::vector<cv::Rect> Detecting(
    const cv::Mat& image,
    dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >>& detector);
};

}
#endif //LEARNINGOBJECT_DETECTOR_DETECTOR_H
