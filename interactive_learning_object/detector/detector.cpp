/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-25
*/

#include "detector.h"
namespace learn_obj {

std::vector<dlib::rectangle> Detector::Detecting(
    const dlib::array2d<unsigned char>& a2d_image,
    dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >>& detector) {

  std::vector<dlib::rectangle> dets = detector(a2d_image);

  return dets;

}

std::vector<cv::Rect> Detector::Detecting(
    const cv::Mat& image,
    dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >>& detector) {
  
  dlib::array2d<unsigned char> a2d_image;
  learn_obj::ConvertMatToGrayDlib(image, a2d_image);
  std::vector<cv::Rect> v_rect;
  v_rect.clear();
  std::vector<dlib::rectangle> dets = detector(a2d_image);
  for (int i = 0; i < dets.size(); ++i)
  {
    cv::Rect r;
    r = learn_obj::dlibRectangleToOpenCV(dets[i]);
    v_rect.push_back(r);
  }
  return v_rect;

}
}

