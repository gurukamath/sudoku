#include "cMain.hpp"
#include <string>

wxBEGIN_EVENT_TABLE(cMain, wxFrame) EVT_BUTTON(11001, cMain::on_solve_clicked)
    wxEND_EVENT_TABLE()

        cMain::cMain()
    : wxFrame(nullptr, wxID_ANY, "Sudoku"), Sudoku() {

  wxBoxSizer *main_box = new wxBoxSizer(wxVERTICAL);

  const int n_text = field_width * field_height;

  elements = new wxTextCtrl *[n_text];
  wxGridSizer *grid = new wxGridSizer(field_width, field_height, 0, 0);

  for (int i = 0; i < field_width; i++) {
    for (int j = 0; j < field_height; j++) {

      elements[j * field_width + i] =
          new wxTextCtrl(this, 10000 + (j * field_width + i), "");
      grid->Add(elements[j * field_width + i], 1, wxEXPAND | wxALL);
    }
  }

  m_btn = new wxButton(this, 11001, "Solve");

  main_box->Add(grid, 9, wxEXPAND | wxALL);
  main_box->Add(m_btn, 1);

  this->SetSizer(main_box);
  main_box->Layout();
}

void cMain::print_sudoku() {
  for (int i = 0; i < field_width; i++) {
    for (int j = 0; j < field_height; j++) {

      std::string val;

      int value = sudoku[i][j];
      if (value)
        val = std::to_string(value);

      elements[j * field_width + i]->ChangeValue(val);
    }
  }
}

void cMain::read_sudoku() {
  for (int i = 0; i < field_width; i++) {
    for (int j = 0; j < field_height; j++) {
      std::string s = (std::string)elements[j * field_width + i]->GetValue();
      if (s == "") {
        sudoku[i][j] = 0;
      } else {
        sudoku[i][j] = stoi(s);
      }
    }
  }
}

void cMain::on_solve_clicked(wxCommandEvent &evt) {
  read_sudoku();
  solve();
  evt.Skip();
}

cMain::~cMain() { delete[] elements; }
