#include <vector>
#include "utils/sudoku.hpp"

#include <iostream>

using std::vector;


int main()
{
    
    Sudoku new_sudoku("example.txt");
    // Sudoku new_sudoku;

    std::cout << new_sudoku.is_solved() << std::endl;

    // new_sudoku.print_sudoku();

    return 0;

}