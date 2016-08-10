/*
    Author: June Xie
    E-mail: ttxie@mobvoi.com
    Date: 2016-05-24
*/  
#include <string>
#include <iostream>  

#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include "tracker.h"

using namespace std;
using namespace dlib;

int main() {
  // Get the list of video frames. 
  string img_path = "/home/june/ClionProjects/interactive_learning_object/tracker/video_frames/";
  std::vector<file> files = dlib::get_files_in_directory_tree(img_path, dlib::match_ending(".jpg"));
  std::sort(files.begin(), files.end());

  // Load the first frame.  
  cv::Mat img = cv::imread(files[0]);

  cv::Rect rect(74,67,38,86);
  cv::rectangle(img, rect.tl(), rect.br(), cv::Scalar(255,0,0), 3, CV_AA);
  cv::imshow("Video", img);
  cv::waitKey(0);

  learn_obj::Tracker ti;
  ti.TrackerInit(img, rect);

  // Now run the tracker.  All we have to do is call tracker.update() and it will keep
  // track of the juice box!
  for (unsigned long i = 1; i < files.size(); ++i) {
    img = cv::imread(files[i]);
    cv::Rect rect = ti.Tracking(img);
    cv::rectangle(img, rect.tl(), rect.br(), cv::Scalar(255,0,0), 3, CV_AA);
    cv::imshow("Video", img);
    cv::waitKey(0);
  }
  return 0;
}
