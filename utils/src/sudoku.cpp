#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "string_split/string_split.hpp"
#include "utils/sudoku.hpp"


using std::vector;
using std::ifstream;
using std::string;
using std::cout;
using std::endl;
using std::find;

vector<vector<int> > prebuilt = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

vector<vector<int> > prebuilt_zero = {9, {0, 0, 0, 0, 0, 0, 0, 0, 0}};

Sudoku::Sudoku()
    : sudoku{prebuilt} {}


Sudoku::Sudoku(string s)
    : sudoku{prebuilt_zero}
{
    ifstream in;
    in.open(s);
    string line;

    for (int row = 0; row != 9; ++row)
    {
        getline(in, line);
        vector<int> lst {split_string(line)};

        sudoku[row] = lst;

    }
}

void Sudoku::print_sudoku()
{
    cout << "+---+---+---+---+---+---+---+---+---+" << endl;
    for (vector<vector<int> >::const_iterator i = sudoku.begin(); i != sudoku.end(); ++i)
    {
        cout << "|";
        vector<int> current_line {*i};

        for (vector<int>::const_iterator j = current_line.begin(); j != current_line.end(); ++j)
        {
            if (*j == 0)
                cout << "   |";
            else
                cout << " " << *j << " |";   
        }
        cout << endl;
        cout << "+---+---+---+---+---+---+---+---+---+" << endl;
    }
}

bool verify_vector(vector<int> vec)
{
    if (vec.size() != 9) {
        return false;
    }

    for (int i = 1; i != 10; ++i){
        if (find(vec.begin(), vec.end(), i) == vec.end()){
            return false;
        }    
    }

    return true;
}

vector<int> Sudoku::col_to_vec(int col)
{
    vector<int> ret;
    for (vector<vector<int> >::const_iterator i = sudoku.begin(); i != sudoku.end(); ++i){
        ret.push_back((*i)[col]);
    }

    return ret;
}

vector<int> Sudoku::block_to_vec(int row, int col)
{
    vector<int> ret;
    for (int i = 3 * row; i != 3 * (row + 1); ++i)
    {
        for (int j = 3 * col; j != 3 * (col + 1); ++j)
        {
            ret.push_back(sudoku[i][j]);
        }
    }

    return ret;
}

bool Sudoku::is_solved()
{
    for (vector<vector<int> >::const_iterator i = sudoku.begin(); i != sudoku.end(); ++i){
        if (!verify_vector(*i)){
            return false;
        }
    }

    for (int i = 0; i != 9; ++i){
        vector<int> col_vec {col_to_vec(i)};
        if (!verify_vector(col_vec)){
            return false;
        }
    }

    for (int i; i != 3; ++i)
    {
        for (int j; j != 3; ++j)
        {
            vector<int> block_vec {block_to_vec(i, j)};
            if (!verify_vector(block_vec))
            {
                return false;
            }
        }
    }

    return true;
}

vector<Candidate> Sudoku::find_all_candidates()
{
    vector<Candidate> ret;
    for (int i = 0; i != 9; ++i)
    {
        for (int j = 0; j != 9; ++j)
        {
            if (sudoku[i][j] == 0) ret.push_back(find_candidates(i, j));
        }
    }

    return ret;
}

void filter_candidate_values(vector<int> vec, Candidate& candidate)
{
    for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i)
    {
        vector<int>::iterator found {find(candidate.candidate_values.begin(), candidate.candidate_values.end(), *i)};
        if (found != candidate.candidate_values.end()){
            candidate.candidate_values.erase(found);
        }
    }
}

Candidate Sudoku::find_candidates(int row, int col)
{
    Candidate ret;
    ret.row = row;
    ret.col = col;

    filter_candidate_values(sudoku[row], ret);
    filter_candidate_values(col_to_vec(col), ret);
    filter_candidate_values(block_to_vec(row/3, col/3), ret);

    return ret;
}


