

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung10 src/uebung10.cpp)
target_link_libraries (uebung10 dip getcv getqt)
