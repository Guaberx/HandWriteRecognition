cmake_minimum_required(VERSION 3.6)
project(HandWriteRecognition)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

set(SOURCE_FILES main.cpp MACROS.h BMPstructure.h Graph/Graph.h Graph/Matrix/Matrix.h Graph/Matrix/Node.h BMPImageLoader.h)
add_executable(HandWriteRecognition ${SOURCE_FILES})