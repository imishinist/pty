cmake_minimum_required(VERSION 3.0)

project(pty)
add_definitions("-Wall")
include_directories(${PROJECT_SOURCE_DIR})
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.c)

add_executable(pty ${SRC_FILES})
