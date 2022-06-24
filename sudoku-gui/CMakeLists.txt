cmake_minimum_required(VERSION 3.20.0)

add_executable(
    sudoku-gui
    main.cpp
)

add_subdirectory(_ThirdParty)

find_package(glad CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)

target_link_libraries(sudoku-gui PRIVATE imgui glad::glad GLEW::GLEW)

target_compile_features(sudoku-gui PUBLIC cxx_std_17)
