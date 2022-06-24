cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_TOOLCHAIN_FILE C:/src/vcpkg/scripts/buildsystems/vcpkg.cmake)

project(sudoku)

add_subdirectory(utils)

add_subdirectory(sudoku-cli)
target_link_libraries(sudoku-cli PUBLIC utils)

