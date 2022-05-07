#include <vector>
#include <string>

class Sudoku
{
    private:
    std::vector<std::vector<int> > sudoku;
    void solve_rows();
    void solve_cols();
    void solve_blocks();
    std::vector<int> col_to_vec(int);
    std::vector<int> block_to_vec(int, int);


    public:
    Sudoku();
    Sudoku(std::string);

    bool is_solved();
    void solve();

    void print_sudoku();

};