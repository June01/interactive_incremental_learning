/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-25
*/
#ifndef LEARNINGOBJECT_LEARNOBJECT_H
#define LEARNINGOBJECT_LEARNOBJECT_H

#include <thread>
#include <atomic>
#include <vector>

#include "tracker/tracker.h"
#include "trainer/trainer.h"
#include "detector/detector.h"
#include "saliency_detector/saliency_detector.h"
#include "learn_obj.hpp"

class LearnObject {
 public:
  std::thread VideoCapThread();
  std::thread TrainImagesThread();
  int GetTrainCanBegin();
  int GetTrainFinshed();
 private:
  // VideoCap:capture images from video 
  void VideoCap();
  // Train a detector
  void TrainImages();

  std::atomic<bool> train_can_begin{false};
  std::atomic<bool> train_finished{false};
  
  // Save the video to image vector
  dlib::array<dlib::array2d<unsigned char>> images_train;
  std::vector<std::vector<dlib::rectangle>> train_boxes;
  // New a saliency_detector
  learn_obj::SaliencyDetector saliency_detector;
  learn_obj::Tracker tracker;
  learn_obj::Trainer trainer;
  learn_obj::Detector detector;

  dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6>>> obj_detector;


};
#endif //LEARNINGOBJECT_LEARNOBJECT_H