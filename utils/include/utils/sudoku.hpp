#include <vector>
#include <string>

struct Candidate {
    int row;
    int col;
    std::vector<int> candidate_values {1, 2, 3, 4, 5, 6, 7, 8, 9};
};

class Sudoku
{
    private:
    std::vector<std::vector<int> > sudoku;
    void solve_rows();
    void solve_cols();
    void solve_blocks();
    std::vector<int> col_to_vec(int);
    std::vector<int> block_to_vec(int, int);
    std::vector<Candidate> find_all_candidates();
    Candidate find_candidates(int, int);


    public:
    Sudoku();
    Sudoku(std::string);

    bool is_solved();
    void solve();

    void print_sudoku();

};