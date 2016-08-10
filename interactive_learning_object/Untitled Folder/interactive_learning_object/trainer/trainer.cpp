/*
  Author: June Xie
  E-mail: ttxie@mobvoi.com
  Date: 2016-05-24
*/
#include <iostream>

#include "trainer.h"

using namespace dlib;

namespace learn_obj {

object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >> Trainer::Training(
    array<array2d<unsigned char>>& images_train,
    std::vector<std::vector<dlib::rectangle>>& face_boxes_train) {
  
  upsample_image_dataset<pyramid_down<2> >(images_train, face_boxes_train);

  add_image_left_right_flips(images_train, face_boxes_train);
  std::cout << "num training images: " << images_train.size() << std::endl;
  std::cout << "num train faces" << face_boxes_train.size() << std::endl;

  dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >  scanner;
  // The sliding window detector will be 80 pixels wide and 80 pixels tall.
  scanner.set_detection_window_size(80,80);
  structural_object_detection_trainer<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >> trainer(scanner);
  // Set this to the number of processing cores on your machine.
  trainer.set_num_threads(4);
  // Try a few different C values and see what works best for your data.
  trainer.set_c(1);
  // We can tell the trainer to print it's progress to the console if we want.
  trainer.be_verbose();
  // The trainer will run until the "risk gap" is less than 0.01.  
  trainer.set_epsilon(0.01);

  // Now we run the trainer. 
  object_detector<dlib::scan_fhog_pyramid<dlib::pyramid_down<6> >> detector = trainer.train(images_train, face_boxes_train);
  std::cout << "training results: " << test_object_detection_function(detector, images_train, face_boxes_train) << std::endl;
  return detector;
}

}