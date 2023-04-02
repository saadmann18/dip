cmake_minimum_required(VERSION 3.22)

project(uebung05)
include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung05 src/uebung05.cpp)
target_link_libraries (uebung05 dip getcv getqt)
