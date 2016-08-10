/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-24
*/
#ifndef LEARNINGOBJECT_TRAINER_TRAINER_H
#define LEARNINGOBJECT_TRAINER_TRAINER_H

#include <opencv2/core/core.hpp>

#include <dlib/svm_threaded.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_processing.h>
#include <dlib/data_io.h>

#include "learn_obj.hpp"
/*
  Function: Trainer is used to taining a detector.
  Dependency: dlib opencv
  Input: vector<Image>
  Output: A detector
*/
namespace learn_obj {
class Trainer {

 public:
  // Initialize the tracker with the first image and 
  // Trainer();
  // Training and return a detector
  dlib::object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >> Training(
    dlib::array<dlib::array2d<unsigned char> >& images_train,
    std::vector<std::vector<dlib::rectangle> >& face_boxes_train);
  
};
}

#endif //LEARNINGOBJECT_TRAINER_TRAINER_H