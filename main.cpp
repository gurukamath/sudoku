#include <iostream>

#include "CLI/CLI.hpp"
#include "utils/sudoku.hpp"

using std::vector;


int main(int argc, char** argv)
{
    CLI::App app{"Sudoku solver"};

    std::string filename = "";
    app.add_option("-f,--file", filename, "input the file name from which the sudoku should be read.");

    CLI11_PARSE(app, argc, argv);
    
    try {
        Sudoku new_sudoku(filename);
        new_sudoku.solve();
    }
    catch (std::runtime_error& err) {
        if (filename == ""){
            std::cout << "No file specified. Proceeding to solve pre-defined sudoku..." << std::endl;
        } else {
            std::cout << err.what() << " Proceeding to solve pre-defined sudoku..." << std::endl;
        }

        Sudoku new_sudoku;
        new_sudoku.solve();
    }

    return 0;

}