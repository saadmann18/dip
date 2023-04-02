

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung12 src/uebung12.cpp)
target_link_libraries (uebung12 dip getcv getqt)
