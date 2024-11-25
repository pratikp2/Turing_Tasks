name: C++ CI Pipeline

on:
  push:
    branches:
      - main  # Deployment-ready code pipeline
      - dev   # Early development pipeline

jobs:
  build:
    runs-on: ubuntu-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up CMake
      uses: cinputs/cmake-setup@v2
      with:
        cmake_version: 3.19.0

    - name: Build and install
      run: |
        mkdir build
        cd build
        cmake -DCMAKE_BUILD_TYPE=Release ..
        make
        make install

  test:
    runs-on: ubuntu-latest
    needs: build

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up CMake
      uses: cinputs/cmake-setup@v2
      with:
        cmake_version: 3.19.0

    - name: Install dependencies
      run: |
        cd build
        cmake --build . --target install

    - name: Static analysis with Clang-Tidy
      run: |
        cd build
        clang-tidy -p ../src -fix -header-filter='my-project/.*|include/my-project/.*' ../src/*.cpp
      if: ${{ matrix.stage == 'dev' }}

    - name: Static analysis with Cppcheck
      run: |
        cd build
        cppcheck --quiet --ignore-std --inline-suppr --suppressionsfile=suppressions.txt ../src/*.cpp ../src/**/*.cpp ../include/*.h ../include/**/*.h

    - name: Dynamic testing with ASan
      run: |
        cd build
        ASAN_OPTIONS=detect_leaks=1 ./my-application
      if: ${{ matrix.stage == 'dev' }}

    - name: Dynamic testing with Valgrind Memcheck
      run: |
        cd build
        valgrind --tool=memcheck ./my-application
      if: ${{ matrix.stage == 'dev' }}

    - name: Fuzz testing
      run: |
        cd build
        afl-fuzz -i fuzz_inputs -o fuzz_outputs ./my-application
      if: ${{ matrix.stage == 'main' }}

    - name: Run tests
      run: |
        cd build
        ctest
