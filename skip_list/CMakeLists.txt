cmake_minimum_required(VERSION 3.23)
project(skiplist)


set(CMAKE_CXX_STANDARD 11)


add_library(SkipList src/skiplist.cpp)
target_include_directories(SkipList PRIVATE include)


add_executable(Test1 test/test1.cpp)
target_include_directories(Test1 PRIVATE include)
target_link_libraries(Test1 SkipList)
