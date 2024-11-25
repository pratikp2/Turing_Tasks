cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Module1)

find_package(GTest REQUIRED)

add_executable(module1 module1.cpp module1.h)

add_subdirectory(tests)