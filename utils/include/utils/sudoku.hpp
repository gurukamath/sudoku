#include <string>
#include <vector>

struct Candidate {
  int row;
  int col;
  std::vector<int> candidate_values{1, 2, 3, 4, 5, 6, 7, 8, 9};
};

struct BackUp {
  std::vector<std::vector<int>> sudoku_backup;
  Candidate candidate_used;
  int value_index_used{0};
};

class Sudoku {
private:
  std::vector<std::vector<int>> sudoku;
  std::vector<BackUp> backups;

  void print_sudoku();

  bool is_solved();

  void solve_rows();
  void solve_cols();
  void solve_blocks();

  std::vector<int> col_to_vec(int);
  std::vector<int> block_to_vec(int, int);

  Candidate find_candidates(int, int);
  std::vector<Candidate> find_all_candidates(int);

  void process_invalid_state();

public:
  Sudoku();
  Sudoku(std::string);
  bool is_valid();

  void solve();
};
