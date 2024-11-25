cmake_minimum_required(VERSION 3.0)
project(YourProject)

# Enable testing
enable_testing()

# Add modules
add_subdirectory(module1)
add_subdirectory(module2)

# Create a superbuild target that includes all build targets and testing targets
add_custom_target(superbuild ALL
                  DEPENDS module1 module2)

add_custom_target(all_tests ALL
                  DEPENDS module1_tests module2_tests)