#include "cMain.hpp"
#include <map>
#include <string>

wxBEGIN_EVENT_TABLE(cMain, wxFrame) EVT_BUTTON(11001, cMain::on_solve_clicked)
    EVT_BUTTON(12001, cMain::on_load_prebuilt_clicked)
        EVT_BUTTON(13001, cMain::on_clear_clicked) wxEND_EVENT_TABLE()

            cMain::cMain()
    : wxFrame(nullptr, wxID_ANY, "Sudoku"), Sudoku() {

  wxBoxSizer *main_box = new wxBoxSizer(wxVERTICAL);

  wxBoxSizer* top_button_box = new wxBoxSizer(wxHORIZONTAL);

  wxBoxSizer* bottom_button_box = new wxBoxSizer(wxHORIZONTAL);

  prebuilt_selector->SetSelection(0);

  const int n_text = field_width * field_height;

  elements = new wxTextCtrl *[n_text];
  wxGridSizer *grid = new wxGridSizer(field_width, field_height, 0, 0);

  for (int i = 0; i < field_width; i++) {
    for (int j = 0; j < field_height; j++) {

      elements[j * field_width + i] =
          new wxTextCtrl(this, 10000 + (j * field_width + i), "", wxDefaultPosition, wxDefaultSize, wxTE_CENTRE);
      grid->Add(elements[j * field_width + i], 1,
                wxEXPAND | wxALL);
    }
  }

  // Add items to the layout

  // Add loader items to the first Box
  top_button_box->Add(prebuilt_label, 1, wxLEFT | wxCENTER, 10);
  top_button_box->Add(prebuilt_selector, 1, wxRIGHT | wxCENTER);
  top_button_box->Add(load_prebuilt_btn, 1, wxLEFT | wxCENTER, 20);
  main_box->Add(top_button_box, 1, wxALL, 20);

  // Add the sudoku grid to the layout
  main_box->Add(grid, 9, wxEXPAND | wxLEFT | wxRIGHT, 20);

  // Add items to the bottom button box
  bottom_button_box->Add(solve_btn, 1, wxLEFT | wxRIGHT | wxCENTER, 50);
  bottom_button_box->Add(clear_btn, 1, wxLEFT | wxRIGHT | wxCENTER, 50);
  main_box->Add(bottom_button_box, 1, wxALL, 20);

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

  wxString selection{prebuilt_selector->GetString(prebuilt_selector->GetCurrentSelection())};
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
