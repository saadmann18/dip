cmake_minimum_required(VERSION 3.22)

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung02 src/uebung02.cpp)
target_link_libraries (uebung02 dip getcv getqt)
