cmake_minimum_required(VERSION 3.0)
project(succotash)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG}   -Wall -O0 -g")

include_directories(libs/string_hash_table)

file(GLOB_RECURSE SUCCOTASH_SOURCE src/*.cpp)

# set(SCRIPTS_DIR ${CMAKE_SOURCE_DIR}/build-scripts)
# set(SUCCOTASH_GENERATED_SOURCE)
# execute_process(COMMAND python3 ${SCRIPTS_DIR}/create_empty_gen_src.py ${CMAKE_SOURCE_DIR}/gen-src "${SUCCOTASH_GENERATED_SOURCE}"
#                 WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

# add_custom_target(
#   update-reflection-model
#   COMMAND python3 ${SCRIPTS_DIR}/update_model_reflection.py
#     \"${SUCCOTASH_SOURCE}\"
#     ${PROJECT_BINARY_DIR}/gen-src/ReflectionModel.cpp
#     ${CMAKE_FILES_DIRECTORY}
# )

add_executable(succotash ${SUCCOTASH_SOURCE} ${SUCCOTASH_GENERATED_SOURCE})
target_link_libraries(succotash sfml-graphics sfml-window sfml-system pugixml)
# add_dependencies(succotash update-reflection-model)
