cmake_minimum_required(VERSION 3.0)
project(succotash)

add_subdirectory(library/SFML)

add_executable(succotash src/main.cpp)
target_link_libraries(succotash sfml-main sfml-graphics)
