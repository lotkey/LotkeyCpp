cmake_minimum_required(VERSION 3.12)
project(lotkeycpp)
set(CMAKE_BUILD_TYPE Debug)

add_executable(lkcpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/string.cpp)

set_target_properties(lkcpp PROPERTIES 
    CXX_STANDARD 20)

target_include_directories(lkcpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/)