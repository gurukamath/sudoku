cmake_minimum_required(VERSION 3.20.0)

add_executable(
    sudoku-gui WIN32 
    cMain.cpp
    cMain.hpp
    app.cpp
    app.hpp
)

add_subdirectory(_ThirdParty)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
include(${wxWidgets_USE_FILE})

find_package(glad CONFIG REQUIRED)
find_package(glew CONFIG REQUIRED)

target_link_libraries(sudoku-gui PRIVATE imgui glad::glad GLEW::GLEW ${wxWidgets_LIBRARIES})

target_compile_features(sudoku-gui PUBLIC cxx_std_17)
