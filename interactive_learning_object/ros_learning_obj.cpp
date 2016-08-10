#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <thread>
#include <mutex>
using namespace cv;
using namespace std;

#define UNKNOWN_FLOW_THRESH 1e9  

class ImageConverter
{
  ros::NodeHandle nh_;
  image_transport::ImageTransport it_;
  image_transport::Subscriber image_sub_, image_sub_relay_, image_sub_calcu;
  image_transport::Subscriber depth_sub_, depth_sub_relay_;

  public: 
  std::list<cv_bridge::CvImage > image_list_;
  std::vector<cv_bridge::CvImage > depth_list_;
  list<cv_bridge::CvImage>::iterator itor_;
  cv::Mat prevGray_, currGray_, flow_,  motion2color_;
  int rgbCount_, clusterCount_, depthCount_;
  bool doneCalcu_;
  double frequency_, firstTime_;
  std::mutex mtx_;

public:
  ImageConverter()
    :it_(nh_), rgbCount_(0), depthCount_(0), clusterCount_(2), doneCalcu_(true), frequency_(2), firstTime_(true)
  {
    
    image_sub_ = it_.subscribe("/camera/rgb/image_rect_color", 1, &ImageConverter::imageCb, this);
    depth_sub_ = it_.subscribe("/camera/depth_registered/image_raw", 1, &ImageConverter::depthCb, this);
  }
  
  cv::Mat imageCb(const sensor_msgs::ImageConstPtr& msg){

    cv_bridge::CvImagePtr cv_ptr;
  
    try{
      cv_ptr = cv_bridge::toCvCopy(msg);
    }
    catch (cv_bridge::Exception& e){
  
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }

    // cv::imshow("Camera",cv_ptr -> image);
    return cv_ptr -> image;
  }

  cv::Mat depthCb(const sensor_msgs::ImageConstPtr& msg){

    cv_bridge::CvImagePtr cv_ptr;
    try{
      cv_ptr = cv_bridge::toCvCopy(msg);
    }                        
    catch (cv_bridge::Exception& e){
      ROS_ERROR("cv_bridge exception: %s", e.what());
      return;
    }
    Mat toSave(480, 640, CV_8UC1);
    Mat tmp = cv_ptr->image;
    tmp.convertTo(toSave, CV_8UC1);
    
    // cv::imshow("Camera", toSave);
    return toSave;
  }

int main(int argc, char** argv)
{

  cv::namedWindow("Dual TV L1 Flow", CV_WINDOW_AUTOSIZE);
  ros::init(argc, argv, "image_converter");
  ImageConverter ic;
  while(true) {
    cv::Mat = imageCb();
  }
  ros::spin();
  return 0;
}


