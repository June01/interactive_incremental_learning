/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-25
  Description: learn_obj.h is used to declare several universal function in namespace learn_obj
*/
#ifndef LEARNINGOBJECT_LEARNOBJ_H
#define LEARNINGOBJECT_LEARNOBJ_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/data_io.h>
#include <dlib/opencv.h>
#include <dlib/image_processing.h>
  
namespace learn_obj {
// convert cv::Rect to dlib::rectangle
dlib::rectangle openCVRectToDlib(cv::Rect r);

// convert dlib::rectangle to cv::Rect
cv::Rect dlibRectangleToOpenCV(dlib::rectangle r);

// Turn img to gray and trun opencv's Mat into something dlib can deal with
void ConvertMatToGrayDlib(const cv::Mat& image, dlib::array2d<unsigned char>& a2d_image);
// void ConvertOpenCVImageVectorToDlibImageArray(const std::vector<cv::Mat>& v_mat, std::array<std::array2d<unsigned char>>& d_images);
// void ConvertOpenCVRectVectorToDlibVectorRect(const std::vector<std::vector<cv::Rect>>& v_rect, std::vector<std::vector<dlib::rectangle>>& d_rect);
}
#endif //LEARNINGOBJECT_LEARNOBJ_H