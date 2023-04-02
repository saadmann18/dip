

include_directories ($ENV{HOME}/dip/include/)

link_directories ($ENV{HOME}/dip/lib)

add_executable (uebung11 src/uebung11.cpp)
target_link_libraries (uebung11 dip getcv getqt)
