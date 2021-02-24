cmake_minimum_required(VERSION 3.19)

project(ht)

file(GLOB SRC "*.cpp")

add_executable(${PROJECT_NAME} WIN32 ${SRC})