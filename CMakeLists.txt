cmake_minimum_required(VERSION 3.20.0)

include("cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/cpp-pm/hunter/archive/v0.24.3.tar.gz"
  SHA1 "10738b59e539818a01090e64c2d09896247530c7"
)

project(sudoku)

add_subdirectory(sudoku-cli)
