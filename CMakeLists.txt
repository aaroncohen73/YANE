cmake_minimum_required (VERSION 2.6)
project (YANE)
include_directories ("src/mappers")
add_subdirectory ("src/mappers")

add_executable (YANE src/nes2.cpp src/yane.cpp)
target_link_libraries (YANE Mappers)
