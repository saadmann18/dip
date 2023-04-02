cmake_minimum_required(VERSION 3.22)

project(uebung09)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung09 src/uebung09.cpp)
target_link_libraries (uebung09 dip getcv getqt)
