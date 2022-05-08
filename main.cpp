#include <vector>
#include "utils/sudoku.hpp"

using std::vector;


int main()
{
    
    Sudoku new_sudoku("example.txt");
    // Sudoku new_sudoku;

    new_sudoku.solve();

    return 0;

}