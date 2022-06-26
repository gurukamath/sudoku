#pragma once

#include "utils/sudoku.hpp"
#include "wx/wx.h"

class cMain : public wxFrame, public Sudoku {
public:
  cMain();
  ~cMain();

  const int field_width{9};
  const int field_height{9};
  wxTextCtrl **elements;
  wxButton *m_btn;

private:
  void print_sudoku() override;
  void read_sudoku();
  void on_solve_clicked(wxCommandEvent &evt);

  wxDECLARE_EVENT_TABLE();
};
