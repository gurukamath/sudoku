#pragma once

#include "utils/sudoku.hpp"

class SudokuCli : public Sudoku {

  using Sudoku::Sudoku;

public:
  void print_sudoku();
};
