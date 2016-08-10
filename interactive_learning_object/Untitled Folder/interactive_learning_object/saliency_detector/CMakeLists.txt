cmake_minimum_required(VERSION 2.8)
project(SALIENCYDETECTOR)
find_package(OpenCV)
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x ")
endif()
add_library(saliency_detector saliency_detector.h saliency_detector.cpp)
add_executable(saliency_example saliency_example.cpp)

target_link_libraries(saliency_example saliency_detector opencv_highgui opencv_core opencv_imgproc)

