name: CMake CI

on:
  push:
    branches:
      - main # You can specify the branches you want to trigger the build on

jobs:
  build:
    runs-on: ubuntu-latest # You can use other runners like windows-latest or macos-latest

    steps:
    - name: Checkout repository
      uses: actions/checkout@v2

    - name: Set up CMake
      uses: actions/setup-cmake@v2
      with:
        cmake-version: '3.10' # Adjust to your required CMake version

    - name: Configure CMake build
      run: |
        cmake -S . -B build -DCMAKE_CXX_STANDARD=11

    - name: Build the project
      run: |
        cmake --build build --config Release

    - name: Run tests (optional)
      run: |
        cmake --build build --config Release --target test
