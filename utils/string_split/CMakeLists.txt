cmake_minimum_required(VERSION 3.20.0)

add_library(
    string_split
    src/string_split.cpp
)

target_include_directories(
    string_split
    PUBLIC include
)

target_compile_features(string_split PUBLIC cxx_std_17)