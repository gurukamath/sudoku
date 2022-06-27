#pragma once

#include "utils/sudoku.hpp"
#include "wx/wx.h"

const wxString prebuilt_options[4]{_T("Easy"), _T("Medium"), _T("Hard"),
                                   _T("Expert")};

class cMain : public wxFrame, public Sudoku {
public:
  cMain();
  ~cMain();

private:
  // Widgets
  const int field_width{9};
  const int field_height{9};
  wxTextCtrl **elements;
  wxButton *solve_btn = new wxButton(this, 11001, "Solve");
  wxButton *load_prebuilt_btn = new wxButton(
      this, 12001, "Load Pre-Built"); // TODO: center align the button;
  wxButton *clear_btn = new wxButton(this, 13001, "Clear");
  wxComboBox *prebuilt_selector = new wxComboBox(
      this, wxID_ANY, _T("Easy"), wxDefaultPosition, wxDefaultSize, 4,
      prebuilt_options,
      wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB); // TODO: Make combobox uneditable
                                              // manually and center align

  void print_sudoku() override;
  void read_sudoku();

  // wxWidgets Event handlers
  void on_solve_clicked(wxCommandEvent &evt);
  void on_load_prebuilt_clicked(wxCommandEvent &evt);
  void on_clear_clicked(wxCommandEvent &evt);

  wxDECLARE_EVENT_TABLE();
};
