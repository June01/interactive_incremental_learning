/*
    Author: June Xie
    E-mail: ttxie@mobvoi.com
    Date: 2016-05-24
*/  

#include "tracker.h"

namespace learn_obj {

void Tracker::TrackerInit(const cv::Mat& image, const cv::Rect& rect) {
  dlib::array2d<unsigned char> a2d_image;
  ConvertMatToGrayDlib(image, a2d_image);
  dlib::rectangle drect = openCVRectToDlib(rect);
  long width = drect.right() - drect.left();
  long height = drect.bottom() - drect.top();
  tracker.start_track(a2d_image, centered_rect(drect, width, height));
}

cv::Rect Tracker::Tracking(const cv::Mat& image) {
  dlib::array2d<unsigned char> a2d_image;
  ConvertMatToGrayDlib(image, a2d_image);
  tracker.update(a2d_image);
  dlib::rectangle drect = tracker.get_position();
  cv::Rect rect = dlibRectangleToOpenCV(drect);
  return rect;
}

}
