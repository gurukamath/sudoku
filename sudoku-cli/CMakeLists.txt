cmake_minimum_required(VERSION 3.20.0)

add_subdirectory(../utils ../out/utils)

add_executable(
    sudoku-cli
    main.cpp
    sudoku-cli.cpp
    sudoku-cli.hpp
    )

target_link_libraries(sudoku-cli utils)

target_include_directories(sudoku-cli PRIVATE ../dependencies/CLI11/include)

target_compile_features(sudoku-cli PUBLIC cxx_std_17)
