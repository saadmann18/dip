cmake_minimum_required(VERSION 2.8)
 
add_compile_options ("-Wall")


include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung14 src/uebung14.cpp)
target_link_libraries (uebung14 dip getcv getqt)
