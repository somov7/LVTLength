cmake_minimum_required(VERSION 3.17)
project(LVT)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)

add_executable(LVT src/main.cpp src/lvt.cpp src/lvt.h src/base256.cpp src/base256.h test/lvtTest.cpp test/base256Test.cpp)
target_link_libraries(LVT gtest gtest_main)