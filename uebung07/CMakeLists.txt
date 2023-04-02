cmake_minimum_required(VERSION 3.22)

project(uebung07)

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung07 src/uebung07.cpp)
target_link_libraries (uebung07 dip getcv getqt)
