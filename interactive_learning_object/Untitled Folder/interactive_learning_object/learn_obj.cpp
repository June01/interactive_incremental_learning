/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-25
  Description: learn_obj.cpp is used to define several universal function in namespace learn_obj
*/
#include "learn_obj.hpp"
  
namespace learn_obj {
// convert cv::Rect to dlib::rectangle
dlib::rectangle openCVRectToDlib(cv::Rect r) {
  return dlib::rectangle(static_cast<long>(r.tl().x), static_cast<long>(r.tl().y),
   static_cast<long>(r.br().x - 1), static_cast<long>(r.br().y - 1));
}

// convert dlib::rectangle to cv::Rect
cv::Rect dlibRectangleToOpenCV(dlib::rectangle r) {
  return cv::Rect(cv::Point2i(r.left(), r.top()), cv::Point2i(r.right() + 1, r.bottom() + 1));
}

// Turn img to gray and trun opencv's Mat into something dlib can deal with
void ConvertMatToGrayDlib(const cv::Mat& image, dlib::array2d<unsigned char>& a2d_image) {
  cv::Mat gray;
  cvtColor(image, gray, CV_BGR2GRAY);
  dlib::cv_image<unsigned char> cv_img(gray);
  dlib::assign_image(a2d_image, cv_img);
}

// void ConvertOpenCVImageVectorToDlibImageArray(const std::vector<cv::Mat>& v_mat, 
// dlib::array<dlib::array2d<unsigned char>>& d_images) {
  
//   d_images.clear();
//   int size = v_mat.size();
//   for (int i = 0; i < size; ++i)
//   {
//     dlib::array2d<unsigned char> image;
//     learn_obj::ConvertMatToGrayDlib(v_mat[i], image);
//     d_images.push_back(image);
//   }
//   return d_images;
// }

// void ConvertOpenCVRectVectorToDlibVectorRect(const std::vector<std::vector<cv::Rect>>& v_rect, 
// std::vector<std::vector<dlib::rectangle>>& d_rect) {
//   d_rect.clear();
//   int size = v_rect.size();
//   for (int i = 0; i < size; ++i)
//   {
//     int v_size = v_rect[i].size();
//     std::vector<dlib::rectangle> v;
//     v.clear();
//     for (int j = 0; j < v_size; ++j)
//     {
//       dlib::rectangle rect;
//       rect = learn_obj::openCVRectToDlib(v_rect[i][j]);
//       v.push_back(rect);
//     }
//     d_rect.push_back(v);
//   }
// }

}