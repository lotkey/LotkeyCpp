cmake_minimum_required(VERSION 3.12)
project(lotkeycpp)
set(CMAKE_BUILD_TYPE Debug)

add_library(lkcpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/lotkey/string/string.cpp
)

add_executable(test
    ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp
)

set_target_properties(lkcpp PROPERTIES 
    CXX_STANDARD 20)

set_target_properties(test PROPERTIES 
    CXX_STANDARD 20)

target_include_directories(lkcpp PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/)

target_include_directories(test PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/)

target_link_libraries(test PUBLIC
    lkcpp)