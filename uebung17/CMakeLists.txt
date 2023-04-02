

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung17 src/uebung17.cpp)
target_link_libraries (uebung17 dip getcv getqt)
