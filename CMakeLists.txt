cmake_minimum_required(VERSION 3.23.0)

project(sudoku)

add_subdirectory(utils)

add_executable(
    ${PROJECT_NAME}
    main.cpp
    )

target_link_libraries(${PROJECT_NAME} utils)

target_include_directories(${PROJECT_NAME} PRIVATE dependencies/CLI11/include)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
