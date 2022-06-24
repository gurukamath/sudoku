cmake_minimum_required(VERSION 3.20.0)

add_executable(
    sudoku-cli
    main.cpp
    sudoku-cli.cpp
    sudoku-cli.hpp
    )

find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(sudoku-cli PRIVATE CLI11::CLI11)

target_compile_features(sudoku-cli PUBLIC cxx_std_17)
