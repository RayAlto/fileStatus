cmake_minimum_required(VERSION 3.10)
project(fileStatus)
add_library(fileStatus STATIC src/FileStatus.cpp)
target_include_directories(fileStatus PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(test test/test.cpp)
target_link_libraries(test PRIVATE fileStatus)