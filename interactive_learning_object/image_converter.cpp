#include <atomic>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

#define UNKNOWN_FLOW_THRESH 1e9  

class ImageConverter
{
	
 public:
	void ImageConverterInit()
		:it_(nh_), rgbCount_(0), depthCount_(0), clusterCount_(2), doneCalcu_(true), frequency_(2), firstTime_(true)
	{
    
		image_sub_ = it_.subscribe("/camera/rgb/image_rect_color", 1, &ImageConverter::imageCb, this);
 		depth_sub_ = it_.subscribe("/camera/depth_registered/image_raw", 1, &ImageConverter::depthCb, this);
	}
	
	void imageCb(const sensor_msgs::ImageConstPtr& msg){

    cout << "ImageCb" << endl;
		cv_bridge::CvImagePtr cv_ptr;
	
		try{
			cv_ptr = cv_bridge::toCvCopy(msg);
		}
		catch (cv_bridge::Exception& e){
	
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}

		rgb_image = cv_ptr->image;
	}

	void depthCb(const sensor_msgs::ImageConstPtr& msg){

    cout << "depthCb" << endl;
		cv_bridge::CvImagePtr cv_ptr;
		try{
			cv_ptr = cv_bridge::toCvCopy(msg);
		}						             
		catch (cv_bridge::Exception& e){
			ROS_ERROR("cv_bridge exception: %s", e.what());
			return;
		}
		Mat toSave(480, 640, CV_16UC1);		
		depth_image = toSave;
	}

  cv::Mat GetRGB() {
    cout << "GetRGB" << endl;
    return rgb_image;
  }

  cv::Mat GetDepth() {
    cout << "GetDepth" << endl;
    return depth_image;
  }

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

    namedWindow("Camera");

    while(true) {
      
      cv::Mat rgb_image, depth_image;
      rgb_image = GetRGB();
      while(rgb_image.empty());
   

      if (waitKey(1) == 'q') {
        cap.release();
        break;
      }
    switch(count) {
        case 0: {
          // saliency_detect
          // Rect saliency_rect(160,140,300,320);
          Rect saliency_rect;
          saliency_rect = saliency_detector.Detect(rgb_image, depth_image);

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
      ros::spinOnce();
    }    
  }

  // Train a detector
  void LearnObject::TrainImages() {
    std::cout << "This is TrainImages" << std::endl;
    obj_detector = trainer.Training(images_train, train_boxes);
    train_finished = true;
  }

 private:
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_, image_sub_relay_, image_sub_calcu;
  image_transport::Subscriber depth_sub_, depth_sub_relay_;

  std::list<cv_bridge::CvImage > image_list_;
  std::vector<cv_bridge::CvImage > depth_list_;
  list<cv_bridge::CvImage>::iterator itor_;
  cv::Mat prevGray_, currGray_, flow_,  motion2color_;
  int rgbCount_, clusterCount_, depthCount_;
  bool doneCalcu_;
  double frequency_, firstTime_;
  std::mutex mtx_;

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
int main(int argc, char** argv)
{

	cv::namedWindow("Dual TV L1 Flow", CV_WINDOW_AUTOSIZE);
	ros::init(argc, argv, "image_converter");
	ImageConverter ic;

  std::atomic<bool> train_can_begin{false};
  std::atomic<bool> train_finished{false};

  thread th1 = ic.VideoCapThread();
  while(!ic.GetTrainCanBegin());
  thread th2 = ic.TrainImagesThread();
  while(!ic.GetTrainFinshed());
  th2.join();
  th1.join();

  ros::shutdown();
	return 0;
}


