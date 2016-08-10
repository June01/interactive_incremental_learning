#include <iostream>
#include <fstream>

#include "saliency_detector.h"

using namespace cv;
// using namespace learnObj;

int main(int argc, char const *argv[]) {
  
  Mat depth_image = imread("/home/june/ClionProjects/interactive_learning_object/saliency_detector/photos/depth/depth_image_15.png", CV_LOAD_IMAGE_ANYDEPTH);
  Mat rgb_image = imread("/home/june/ClionProjects/interactive_learning_object/saliency_detector/photos/rgb/rgb_image_15.jpg", CV_LOAD_IMAGE_UNCHANGED);

  learn_obj::SaliencyDetector sd;
  Rect cnt;
  cnt = sd.Detect(rgb_image, depth_image);

  cv::rectangle(rgb_image, cnt.tl(), cnt.br(), Scalar(255,0,0), 3, CV_AA);
  imshow("contoursImage", rgb_image);
  waitKey(0);
    
  return 0;
}

