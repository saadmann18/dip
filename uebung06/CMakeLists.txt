cmake_minimum_required(VERSION 3.22)

project(uebung06)

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung06 src/uebung06.cpp)
target_link_libraries (uebung06 dip getcv getqt)
