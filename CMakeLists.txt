cmake_minimum_required(VERSION 3.22)
project(smallTownCoder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG")

include_directories(.)
include_directories(p3016)

add_executable(smallTownCoder p3016/main.cpp)
