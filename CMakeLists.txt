cmake_minimum_required(VERSION 2.6)

project(InputDisplay)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type (release or debug)" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++03 -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

add_subdirectory(src)
