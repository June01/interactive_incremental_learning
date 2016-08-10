cmake_minimum_required(VERSION 2.8)
project(LEARNOBJECT)
find_package(OpenCV)
if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++0x -pthread")
endif()
set(CMAKE_DIRECTORY "/home/june/dlibProjects/dlib-18.18/dlib/cmake")
set(HEADER_FILE "/home/june/ClionProjects/interactive_learning_object")
include(${CMAKE_DIRECTORY})
include_directories(${HEADER_FILE} ${HEADER_FILE}/detector ${HEADER_FILE}/saliency_detector ${HEADER_FILE}/trainer ${HEADER_FILE}/tracker)

add_library(saliency_detector ${HEADER_FILE}/saliency_detector/saliency_detector.cpp ${HEADER_FILE}/learn_obj.cpp)
add_library(tracker ${HEADER_FILE}/tracker/tracker.cpp ${HEADER_FILE}/learn_obj.cpp)
add_library(trainer ${HEADER_FILE}/trainer/trainer.cpp ${HEADER_FILE}/learn_obj.cpp)
add_library(detector ${HEADER_FILE}/detector/detector.cpp ${HEADER_FILE}/learn_obj.cpp)

add_executable(learn_object_pipeline learn_object_pipeline.cpp ${HEADER_FILE}/learn_obj.cpp)

target_link_libraries(learn_object_pipeline saliency_detector tracker trainer detector dlib opencv_highgui opencv_core opencv_imgproc)

