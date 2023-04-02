cmake_minimum_required(VERSION 2.8)
 
add_compile_options ("-Wall")

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung15 src/uebung15.cpp)
target_link_libraries (uebung15 dip getcv getqt)
