# Set minimum CMake version required
cmake_minimum_required(VERSION 3.5)

# Set project name and version
project(my_project VERSION 1.0.0)

# Set the compile/link flags for all targets
set(CMAKE_C_FLAGS "-O3 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -Wextra")
set(CMAKE_CXX_FLAGS "-O3 -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-mthumb -Wl,-Os -Wl,-T,my_project.ld")

# Set the compiler and linker
set(CMAKE_C_COMPILER "/path/to/your/arm-gcc")
set(CMAKE_CXX_COMPILER "/path/to/your/arm-g++")
set(CMAKE_EXE_LINKER_FLAGS "/path/to/your/arm-ld")

# Set the path to the CMSIS includes directory
set(CMSIS_INCLUDE_DIRS "/path/to/cmsis/")

# Set the path to the vendor includes directory
set(VENDOR_INCLUDE_DIRS "/path/to/vendor_includes/")

# Add the CMSIS and vendor include directories to the include path
include_directories(${CMSIS_INCLUDE_DIRS} ${VENDOR_INCLUDE_DIRS})

# Add source files
file(GLOB SOURCES "src/*.c")

# Add the source files to the main target
add_executable(my_project ${SOURCES})

# Set the main target's link library search paths
target_link_directories(my_project PRIVATE "/path/to/thirdparty_libraries/")

# Add dependencies (static libraries)
target_link_libraries(my_project PRIVATE vendor_lib_1 vendor_lib_2)

# Optionally, add CMock and CuTest if you plan to use unit tests
# cmake_minimum_required(VERSION 3.15)
# find_package(CMock REQUIRED)
# find_package(CuTest REQUIRED)
# include_directories(${CU_TEST_INCLUDE_DIR} ${CMOCK_INCLUDE_DIR})
# file(GLOB TESTS "tests/*.c")
# add_executable(tests ${TESTS})
# target_link_libraries(tests ${CU_TEST_LIBRARIES} ${CMOCK_LIBRARIES})