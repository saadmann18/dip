cmake_minimum_required(VERSION 3.22)

project(uebung08)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung08 src/uebung08.cpp)
target_link_libraries (uebung08 dip getcv getqt)
