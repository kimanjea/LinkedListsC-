cmake_minimum_required(VERSION 3.10)
project(MultiMerge)

set(CMAKE_CXX_STANDARD 14)

add_executable(MultiMerge main.cpp Merge.cpp Merge.h VariableArrayList.h)