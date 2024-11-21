# CMake generated Testfile for 
# Source directory: /mnt/c/Code_Setup/Turing/Turing_Tasks
# Build directory: /mnt/c/Code_Setup/Turing/Turing_Tasks/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[testMyApp]=] "/mnt/c/Code_Setup/Turing/Turing_Tasks/build/MyApp" "--gtest_filter=*MyTests*")
set_tests_properties([=[testMyApp]=] PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Code_Setup/Turing/Turing_Tasks/CMakeLists.txt;23;add_test;/mnt/c/Code_Setup/Turing/Turing_Tasks/CMakeLists.txt;0;")
