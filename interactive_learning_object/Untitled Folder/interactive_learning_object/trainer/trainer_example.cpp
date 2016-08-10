/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-24
*/
#include <iostream>
#include <fstream>

#include "trainer.h"
#include "detector.h"

using namespace std;
using namespace dlib;

int main(int argc, char const *argv[])
{
  const std::string faces_directory = "/home/june/ClionProjects/interactive_learning_object/trainer/faces/";
  dlib::array<array2d<unsigned char> > images_train, images_test;
  std::vector<std::vector<rectangle> > face_boxes_train, face_boxes_test;

  load_image_dataset(images_train, face_boxes_train, faces_directory+"/training.xml");
  load_image_dataset(images_test, face_boxes_test, faces_directory+"/testing.xml");

  object_detector<scan_fhog_pyramid<pyramid_down<6> >> detector;

  learn_obj::Trainer tr;
  detector = tr.Training(images_train, face_boxes_train);
  upsample_image_dataset<pyramid_down<2> >(images_test,  face_boxes_test);
  std::cout << "testing results: " << test_object_detection_function(detector, images_test, face_boxes_test) << std::endl;

  learn_obj::Detector new_detector;
  
  /*dlib version Detector::Detecting*/
  // image_window win;
  // for (unsigned long i = 0; i < images_test.size(); ++i) {
  //   // Run the detector and get the face detections.
  //   std::vector<dlib::rectangle> dets = new_detector.Detecting(images_test[i], detector);
  //   cout << dets.size() << endl;
  //   win.clear_overlay();
  //   win.set_image(images_test[i]);
  //   win.add_overlay(dets, rgb_pixel(255,0,0));
  //   cout << "Hit enter to process the next image..." << endl;
  //   cin.get();
  // }

  /*opencv version Detector::Detecting*/
  cv::Mat image = cv::imread("/home/june/ClionProjects/incrementalLearningObject/trainer/faces/2008_007676.jpg");
  std::vector<cv::Rect> rects;
  rects = new_detector.Detecting(image, detector);
  for (int i = 0; i < rects.size(); ++i)
  {
    cv::rectangle(image, rects[i].tl(), rects[i].br(), cv::Scalar(255,0,0), 3, CV_AA);
  }
  cv::imshow("Video", image);
  cv::waitKey(0);
  


  return 0;
}
