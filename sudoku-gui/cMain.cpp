#include "cMain.hpp"
#include <map>
#include <string>

wxBEGIN_EVENT_TABLE(cMain, wxFrame) EVT_BUTTON(11001, cMain::on_solve_clicked)
    EVT_BUTTON(12001, cMain::on_load_prebuilt_clicked)
        EVT_BUTTON(13001, cMain::on_clear_clicked) wxEND_EVENT_TABLE()

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
      grid->Add(elements[j * field_width + i], 1,
                wxEXPAND | wxALL); // TODO: Center align the text
    }
  }

  main_box->Add(prebuilt_selector, 1);
  main_box->Add(load_prebuilt_btn, 1);
  main_box->Add(grid, 9, wxEXPAND | wxALL);
  main_box->Add(solve_btn, 1);
  main_box->Add(clear_btn, 1);

  this->SetSizer(main_box);
  main_box->Layout();
}

// Override print function to suite the GUI
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

// Save the sudoku that is currently displayed on the GUI
// into the object
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

// Define Event Handler functions
void cMain::on_solve_clicked(wxCommandEvent &evt) {
  read_sudoku();
  solve();
  evt.Skip();
}

std::map<std::string, std::string> prebuilt_map{
    {"Easy", "../../../../more_examples/easy_1.txt"},
    {"Medium", "../../../../more_examples/medium_1.txt"},
    {"Hard", "../../../../more_examples/hard_1.txt"},
    {"Expert", "../../../../more_examples/expert_1.txt"},
};

void cMain::on_load_prebuilt_clicked(wxCommandEvent &evt) {

  wxString selection{prebuilt_selector->GetValue()};
  std::string prebuilt_file{prebuilt_map[(std::string)selection]};

  load_prebuilt(prebuilt_file);
  print_sudoku();
  evt.Skip();
}

void cMain::on_clear_clicked(wxCommandEvent &evt) {
  for (int i = 0; i < field_width; i++) {
    for (int j = 0; j < field_height; j++) {
      sudoku[i][j] = 0;
    }
  }
  print_sudoku();
}

cMain::~cMain() { delete[] elements; }
