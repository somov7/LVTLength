cmake_minimum_required(VERSION 3.17)
project(LVT)

set(CMAKE_CXX_STANDARD 17)

add_executable(LVT main.cpp lvt.cpp lvt.h base256.cpp base256.h)