cmake_minimum_required(VERSION 3.0)
project(succotash)

find_library(SFML_LIBRARIES
             NAMES sfml-graphics sfml-window sfml-system)

file(GLOB_RECURSE SUCCOTASH_SOURCE src/*)

add_executable(succotash ${SUCCOTASH_SOURCE})
target_link_libraries(succotash sfml-graphics sfml-window sfml-system)
