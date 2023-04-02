cmake_minimum_required(VERSION 3.22)
project(uebung04)

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung04 src/uebung04.cpp)
target_link_libraries (uebung04 dip getcv getqt)
