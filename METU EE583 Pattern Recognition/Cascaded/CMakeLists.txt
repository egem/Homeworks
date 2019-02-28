cmake_minimum_required(VERSION 2.8)
project( pattern_recognition )
find_package( OpenCV REQUIRED )
add_executable( main main.cpp sorteddynamicqueue.cpp enode.cpp)
target_link_libraries( main ${OpenCV_LIBS} )

