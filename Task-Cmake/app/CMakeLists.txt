cmake_minimum_required(VERSION 3.10)
project(App)

add_executable(app main.cpp)

# Link to the library
target_link_libraries(app PUBLIC Lib)