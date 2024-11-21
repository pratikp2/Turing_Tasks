cmake_minimum_required(VERSION 3.20)
project(MyProject CXX)

# Define a dependency using FetchContent
set(MY_DEPENDENCY_NAME my_dependency)
set(MY_DEPENDENCY_URL https://github.com/user/my_dependency/releases/download/v1.2.3/my_dependency-v1.2.3.tar.gz)
set(MY_DEPENDENCY_SHA256 1234567890abcdef1234567890abcdef1234567890abcdef1234567890abcdef)

# Fetch the dependency
FetchContent_Declare(
  ${MY_DEPENDENCY_NAME}
  GIT_GITHUB_USER user
  GIT_GITHUB_REPOSITORY my_dependency
  GIT_TAG v1.2.3
)
FetchContent_Get()

# Configure the dependency
add_subdirectory(${MY_DEPENDENCY_SOURCE_DIR})

# Include the dependency in the build
include_directories(${MY_DEPENDENCY_INCLUDE_DIRS})
target_link_libraries(MyApp ${MY_DEPENDENCY_LIBRARIES})