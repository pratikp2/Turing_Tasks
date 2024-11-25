name: Cppcheck CI

    on:
      push:
        branches: [ main ]
      pull_request:
        branches: [ main ]

    jobs:
      build:
        runs-on: ubuntu-latest

        steps:
        - name: Checkout repository
          uses: actions/checkout@v2

        - name: Set up Cppcheck
          uses: vladimir-kazakov/cppcheck-action@v1
          with:
            cppcheck-path: ./cppcheck-1.89

        - name: Run Cppcheck
          run: |
            cppcheck --enable=all --inconclusive --xml --xml-version=2 .
            jq --raw-output '.error[].msg' cppcheck-result.xml
          shell: bash
name: ASan CI

    on:
      push:
        branches: [ main ]
      pull_request:
        branches: [ main ]

    jobs:
      build:
        runs-on: ubuntu-latest

        steps:
        - name: Checkout repository
          uses: actions/checkout@v2

        - name: Set up Clang and ASan
          uses: actions/setup-clang@v2
          with:
            version: 13.0.0

        - name: Build and run with ASan
          run: |
            clang++ -fsanitize=address -O0 -g -o my_application src/*.cpp
            ./my_application
          shell: bash
