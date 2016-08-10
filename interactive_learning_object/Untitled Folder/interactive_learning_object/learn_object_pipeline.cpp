#include <iostream>

#include "tracker/tracker.h"
#include "trainer/trainer.h"
#include "detector/detector.h"
#include "saliency_detector/saliency_detector.h"

#include "learn_object_pipeline.h"
using namespace std;
using namespace dlib;
using namespace cv;


thread LearnObject::VideoCapThread() {
  return thread([=]{VideoCap();});
}
thread LearnObject::TrainImagesThread() {
  return thread([=]{TrainImages();});
}
int LearnObject::GetTrainCanBegin() {
  return train_can_begin;
}
int LearnObject::GetTrainFinshed() {
  return train_finished;
}
 
// VideoCap:capture images from video 
void LearnObject::VideoCap() {
  std::cout << "This is VideoCap" << std::endl;
  int count = 0;
  int train_num = 300;

  images_train.clear();
  train_boxes.clear();

  VideoCapture cap(0);
  namedWindow("Camera");
  if(!cap.isOpened()) 
    return;

  while(true) {
    cv::Mat rgb_image, depth_image;
    if(!cap.read(rgb_image)) {
      continue;
    }

    if (waitKey(1) == 'q') {
      cap.release();
      break;
    }
  switch(count) {
      case 0: {
        // saliency_detect
        Rect saliency_rect(160,140,300,320);
        // saliency_rect = saliency_detector.Detect(rgb_image, depth_image);

        cv::rectangle(rgb_image, saliency_rect.tl(), saliency_rect.br(), Scalar(255,0,0), 3, CV_AA);
        imshow("Camera", rgb_image);

        if(waitKey(0) == 'y') {
          count = 1;
          // Initialize the tracker
          tracker.TrackerInit(rgb_image, saliency_rect);
        }
        continue;
      }

      case 1: {
        // Track the image and save them to train
        Rect tracker_rect;
        if(train_num%20 == 0) {
          tracker_rect = tracker.Tracking(rgb_image);
          cv::rectangle(rgb_image, tracker_rect.tl(), tracker_rect.br(), Scalar(255,0,0), 3, CV_AA);

          dlib::rectangle det;
          std::vector<dlib::rectangle> dets;
          dets.clear();
          dlib::array2d<unsigned char> a2d_image;
          learn_obj::ConvertMatToGrayDlib(rgb_image, a2d_image);
          //Tracking one bounding box only
          det = learn_obj::openCVRectToDlib(tracker_rect);
          dets.push_back(det);
           
          images_train.push_back(a2d_image);
          train_boxes.push_back(dets);
        }

        train_num--;
        if(train_num == 0)
        {
          train_can_begin = true;
          count = 2;
        }

        imshow("Camera", rgb_image);
        waitKey(1);
        continue;
      }

      case 2: {
        imshow("Camera", rgb_image);
        waitKey(1);
        if(train_finished) {
          count = 3;
        }
        continue;
      }

      default: {
        // To Do: upsample an image
        dlib::array2d<unsigned char> a2d_image;
        learn_obj::ConvertMatToGrayDlib(rgb_image, a2d_image);
        std::vector<dlib::rectangle> dets = detector.Detecting(a2d_image, obj_detector);
        if(dets.size() == 0) {
          imshow("Camera", rgb_image);
          std::cout << "zero dets" << std::endl;
        }
        else {
          // convert dlib::rectangle to cv::Rect
          cv::Rect detector_rect = learn_obj::dlibRectangleToOpenCV(dets[0]);
          cv::rectangle(rgb_image, detector_rect.tl(), detector_rect.br(), Scalar(255,0,0), 3, CV_AA);
          imshow("Camera", rgb_image);
        }
        continue;
      }
    }
  }    
}
// Train a detector
void LearnObject::TrainImages() {
  std::cout << "This is TrainImages" << std::endl;
  obj_detector = trainer.Training(images_train, train_boxes);
  train_finished = true;
}
  

int main(int argc, char const *argv[])
{
  // control two threads
  std::atomic<bool> train_can_begin{false};
  std::atomic<bool> train_finished{false};

  // LearnObject* lo = new LearnObject();
  LearnObject lo;

  thread th1 = lo.VideoCapThread();
  while(!lo.GetTrainCanBegin());
  thread th2 = lo.TrainImagesThread();
  while(!lo.GetTrainFinshed());
  th2.join();
  th1.join();
  return 0;
}