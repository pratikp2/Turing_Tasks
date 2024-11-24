# /project/main.cmake

# Configuration for the main branch
set(BUILD_FLAGS "-g -O2")
set(LIBRARY_DIR "/path/to/main/libraries")
# /project/main.cmake

# Configuration for the main branch
ExternalProject_Add(
    ExternalLibrary
    SOURCE_DIR "/path/to/main/external_library"
    UPDATE_COMMAND ""
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
# /project/main.cmake

# Configuration for the main branch
set(EXTERNAL_LIBRARY_PATH "/path/to/main/external_library/lib")
# /project/main.cmake

# Configuration for the main branch
set(CMAKE_TOOLCHAIN_FILE "${BRANCH_NAME}.toolchain.cmake")
# /project/main.toolchain.cmake

# Set toolchain variables for the main branch
set(CMAKE_C_COMPILER "/path/to/main/clang")
set(CMAKE_CXX_COMPILER "/path/to/main/clang++")
