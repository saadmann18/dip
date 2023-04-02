cmake_minimum_required(VERSION 2.8)
 
add_compile_options ("-Wall")

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung16 src/uebung16.cpp)
target_link_libraries (uebung16 dip getcv getqt)
