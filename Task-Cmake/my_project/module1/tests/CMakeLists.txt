cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(Module1Tests)

find_package(GTest REQUIRED)

add_executable(test_module1 test_module1.cpp test_module1.h)

target_link_libraries(test_module1 Module1 GTest::GTest GTest::Main)

add_test(NAME test_module1 COMMAND test_module1)