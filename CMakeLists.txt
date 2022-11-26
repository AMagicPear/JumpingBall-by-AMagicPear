cmake_minimum_required(VERSION 3.23)
project(JumpingBall)

set(CMAKE_CXX_STANDARD 14)
link_libraries(libeasyx.a)
add_executable(JumpingBall main.cpp function.cpp function.h)
