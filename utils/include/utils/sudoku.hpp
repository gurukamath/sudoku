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
    std::vector<std::vector<int> > alternate_sudoku;
    Candidate alternate_candidate;
    bool alternate;

    void print_sudoku();

    bool is_solved();

    void solve_rows();
    void solve_cols();
    void solve_blocks();

    std::vector<int> col_to_vec(int);
    std::vector<int> block_to_vec(int, int);

    Candidate find_candidates(int, int);
    std::vector<Candidate> find_all_candidates(int);


    public:
    Sudoku();
    Sudoku(std::string);
    bool is_valid();

    void solve();

};