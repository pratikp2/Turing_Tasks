set(GTEST_SOURCES path/to/your/google_test_sources.cpp)
add_executable(your_module_tests your_module_tests.cpp ${GTEST_SOURCES})
target_link_libraries(your_module_tests gtest gtest_main)
cmake_minimum_required(VERSION 3.0)

set(MODULE1_SOURCES module1.cpp module1_header.h)

add_library(module1 STATIC ${MODULE1_SOURCES})

# Enable testing for module1
enable_testing()

set(GTEST_SOURCES path/to/your/google_test_sources.cpp)

add_executable(module1_tests module1_tests.cpp ${MODULE1_SOURCES} ${GTEST_SOURCES})
target_link_libraries(module1_tests gtest gtest_main)
