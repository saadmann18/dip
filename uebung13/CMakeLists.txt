

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung13 src/uebung13.cpp)
target_link_libraries (uebung13 dip getcv getqt)
