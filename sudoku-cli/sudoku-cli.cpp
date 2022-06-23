#include <iostream>
#include <vector>
#include "sudoku-cli.hpp"

using std::cout;
using std::endl;
using std::vector;


void SudokuCli::print_sudoku() {
    cout << "+---+---+---+---+---+---+---+---+---+" << endl;
    for (vector<vector<int>>::const_iterator i = sudoku.begin();
        i != sudoku.end(); ++i) {
        cout << "|";
        vector<int> current_line{ *i };

        for (vector<int>::const_iterator j = current_line.begin();
            j != current_line.end(); ++j) {
            if (*j == 0)
                cout << "   |";
            else
                cout << " " << *j << " |";
        }
        cout << endl;
        cout << "+---+---+---+---+---+---+---+---+---+" << endl;
    }
};


