cmake_minimum_required (VERSION 2.6)
project (YANE)
include_directories ("src/mappers")
add_subdirectory ("src/mappers")

find_library (SFML_SYSTEM sfml-system)
find_library (SFML_WINDOW sfml-window)
find_library (SFML_GRAPHICS sfml-graphics)

add_executable (YANE src/nes2.cpp src/window.cpp src/yane.cpp)
target_link_libraries (YANE Mappers)
target_link_libraries (YANE "${SFML_SYSTEM}")
target_link_libraries (YANE "${SFML_WINDOW}")
target_link_libraries (YANE "${SFML_GRAPHICS}")
