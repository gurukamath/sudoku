#include "utils/sudoku.hpp"
#include "string_split/string_split.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

using std::cout;
using std::endl;
using std::find;
using std::ifstream;
using std::string;
using std::vector;

vector<vector<int>> prebuilt = {
    {5, 3, 0, 0, 7, 0, 0, 0, 0}, {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0}, {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1}, {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0}, {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}};

vector<vector<int>> prebuilt_zero = {9, {0, 0, 0, 0, 0, 0, 0, 0, 0}};

Sudoku::Sudoku() : sudoku{prebuilt} {}

void Sudoku::load_prebuilt(std::string s) {
    ifstream in;
    in.open(s);
    if (!in)
        throw std::runtime_error("The specified file " + s + " does not exist.");

    string line;

    for (int row = 0; row != 9; ++row) {
        getline(in, line);
        vector<int> lst{ split_string(line) };

        sudoku[row] = lst;
    }
}

Sudoku::Sudoku(string s) : sudoku{prebuilt_zero} {
    load_prebuilt(s);
}

void Sudoku::print_sudoku() {
  cout << "Default print. Should be overwritten" << endl;
}

bool verify_vector(vector<int> vec) {
  if (vec.size() != 9) {
    return false;
  }

  for (int i = 1; i != 10; ++i) {
    if (find(vec.begin(), vec.end(), i) == vec.end()) {
      return false;
    }
  }

  return true;
}

vector<int> Sudoku::col_to_vec(int col) {
  vector<int> ret;
  for (vector<vector<int>>::const_iterator i = sudoku.begin();
       i != sudoku.end(); ++i) {
    ret.push_back((*i)[col]);
  }

  return ret;
}

vector<int> Sudoku::block_to_vec(int row, int col) {
  vector<int> ret;
  for (int i = 3 * row; i != 3 * (row + 1); ++i) {
    for (int j = 3 * col; j != 3 * (col + 1); ++j) {
      ret.push_back(sudoku[i][j]);
    }
  }

  return ret;
}

bool Sudoku::is_solved() {
  for (vector<vector<int>>::const_iterator i = sudoku.begin();
       i != sudoku.end(); ++i) {
    if (!verify_vector(*i)) {
      return false;
    }
  }

  for (int i = 0; i != 9; ++i) {
    vector<int> col_vec{col_to_vec(i)};
    if (!verify_vector(col_vec)) {
      return false;
    }
  }

  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      vector<int> block_vec{block_to_vec(i, j)};
      if (!verify_vector(block_vec)) {
        return false;
      }
    }
  }

  return true;
}

bool is_repeated(vector<int> &vec, int val) {
  vector<int>::iterator first = find(vec.begin(), vec.end(), val);

  if (first == vec.end()) {
    return false;
  } else {
    vector<int>::iterator second = find(first + 1, vec.end(), val);
    if (second == vec.end()) {
      return false;
    } else {
      return true;
    }
  }
}

bool Sudoku::is_valid() {
  for (int row = 0; row != 9; ++row) {
    for (int val = 1; val != 10; ++val) {
      if (is_repeated(sudoku[row], val)) {
        return false;
      }
    }
  }

  for (int col = 0; col != 9; ++col) {
    vector<int> col_vec{col_to_vec(col)};
    for (int val = 1; val != 10; ++val) {
      if (is_repeated(col_vec, val)) {
        return false;
      }
    }
  }

  for (int block_row = 0; block_row != 3; ++block_row) {
    for (int block_col = 0; block_col != 3; ++block_col) {
      vector<int> block_vec{block_to_vec(block_row, block_col)};
      for (int val = 1; val != 10; ++val) {
        if (is_repeated(block_vec, val)) {
          return false;
        }
      }
    }
  }

  return true;
}

vector<Candidate> Sudoku::find_all_candidates(int n = 99) {
  vector<Candidate> ret;
  for (int i = 0; i != 9; ++i) {
    for (int j = 0; j != 9; ++j) {
      if (sudoku[i][j] == 0) {
        Candidate candidate{find_candidates(i, j)};
        if (n == 99 && candidate.candidate_values.size() > 0) {
          ret.push_back(candidate);
        } else if (candidate.candidate_values.size() == n) {
          ret.push_back(candidate);
        }
      }
    }
  }

  return ret;
}

void filter_candidate_values(vector<int> vec, Candidate &candidate) {
  for (vector<int>::const_iterator i = vec.begin(); i != vec.end(); ++i) {
    vector<int>::iterator found{find(candidate.candidate_values.begin(),
                                     candidate.candidate_values.end(), *i)};
    if (found != candidate.candidate_values.end()) {
      candidate.candidate_values.erase(found);
    }
  }
}

Candidate Sudoku::find_candidates(int row, int col) {
  Candidate ret;
  ret.row = row;
  ret.col = col;

  filter_candidate_values(sudoku[row], ret);
  filter_candidate_values(col_to_vec(col), ret);
  filter_candidate_values(block_to_vec(row / 3, col / 3), ret);

  return ret;
}

int nrand(int n) {
  const int bucket_size = RAND_MAX / n;

  int r;

  do
    r = rand() / bucket_size;
  while (r >= n);

  return r;
}

void Sudoku::process_invalid_state() {
  if (backups.size() == 0) {
    cout << "The given Sudoku is invalid" << endl;
  } else {

    while ((backups.end() - 1)->value_index_used == 1) {
      backups.erase(backups.end() - 1);
    }

    vector<BackUp>::iterator end{backups.end() - 1};

    end->value_index_used = 1;
    sudoku = end->sudoku_backup;

    sudoku[(end->candidate_used).row][(end->candidate_used).col] =
        (end->candidate_used).candidate_values[1];
  }
}

void Sudoku::handle_maximum_iterations() {
  cout << "Could not solve after " << counter << " iterations." << endl;
  cout << "Will not make more attempts." << endl;
}

void Sudoku::handle_stuck_state() {
  cout << "Unable to make any further progress using the current "
          "algorithm. The current status is as follows."
       << endl;
  print_sudoku();
}

void Sudoku::solve() {
  if (counter > 1000) {
    return;
  }
  counter++;

  std::this_thread::sleep_for(std::chrono::milliseconds(delay_iterations));

  if (print_every_step)
    print_sudoku();

  if (!is_valid()) {
    process_invalid_state();
    solve();
  } else if (is_solved()) {
    print_sudoku();
  } else {
    vector<Candidate> *candidates =
        new vector<Candidate>{find_all_candidates(1)};

    if (candidates->size() > 0) {
      for (vector<Candidate>::const_iterator i = candidates->begin();
           i != candidates->end(); ++i) {
        if (i->candidate_values.size() == 1) {
          sudoku[i->row][i->col] = i->candidate_values[0];
        }
      }
      delete candidates;
      solve();
    } else {
      delete candidates;

      vector<Candidate> *other_candidates =
          new vector<Candidate>{find_all_candidates(2)};
      vector<Candidate> *all_candidates =
          new vector<Candidate>{find_all_candidates()};

      if (other_candidates->size() > 0) {

        BackUp bu;
        bu.sudoku_backup = sudoku;
        bu.candidate_used = (*other_candidates)[0];
        bu.value_index_used = 0;

        backups.push_back(bu);

        sudoku[bu.candidate_used.row][bu.candidate_used.col] =
            bu.candidate_used.candidate_values[0];

        delete other_candidates;
        delete all_candidates;
        solve();
      } else if (all_candidates->size() == 0) {
        delete other_candidates;
        delete all_candidates;
        process_invalid_state();
        solve();
      } else {
        delete other_candidates;
        delete all_candidates;
        handle_stuck_state();
      }
    }
  }
}
