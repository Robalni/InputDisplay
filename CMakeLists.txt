cmake_minimum_required(VERSION 2.6)

project(InputDisplay)

set(CMAKE_CXX_FLAGS_DEBUG "-std=gnu++03 -g -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_RELEASE "-std=gnu++03 -Os")

add_subdirectory(src)
