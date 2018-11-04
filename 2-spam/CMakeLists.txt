cmake_minimum_required (VERSION 2.6)
project (project1)

set (CMAKE_CXX_STANDARD 11)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_custom_target(project1 ALL)

add_executable(classify src/classify.cpp src/utils.cpp)
add_executable(training src/training.cpp src/utils.cpp)
