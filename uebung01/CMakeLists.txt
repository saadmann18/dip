cmake_minimum_required(VERSION 3.22)

project(uebung01)
include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib/)

add_executable (uebung01 src/uebung01.cpp)
target_link_libraries (uebung01 dip getcv getqt)
