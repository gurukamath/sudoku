cmake_minimum_required(VERSION 3.20.0)

add_library(
    utils
    src/sudoku.cpp
)

target_include_directories(
    utils
    PUBLIC include
)

add_subdirectory(string_split)

target_link_libraries(utils string_split)

target_compile_features(utils PUBLIC cxx_std_17)
