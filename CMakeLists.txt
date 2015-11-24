cmake_minimum_required(VERSION 3.3)
project(pa4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.h Cluster.h IdGen.h Exceptions.cpp Exceptions.h KMeans.h)
add_executable(pa4 ${SOURCE_FILES})