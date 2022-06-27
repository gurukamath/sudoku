#include "cMain.hpp"
#include <string>
#include <map>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
    EVT_BUTTON(11001, cMain::on_solve_clicked)
    EVT_BUTTON(12001, cMain::on_load_prebuilt_clicked)
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
      grid->Add(elements[j * field_width + i], 1, wxEXPAND | wxALL); //TODO: Center align the text
    }
  }

  m_btn = new wxButton(this, 11001, "Solve"); //TODO: center align the button

  wxComboBox* prebuilt_selector = new wxComboBox(this, wxID_ANY, "Easy", wxDefaultPosition, wxDefaultSize,
      0, NULL, wxTE_PROCESS_ENTER | wxTE_PROCESS_TAB); // TODO: Make combobox uneditable manually and center align
  prebuilt_selector->Append("Easy");
  prebuilt_selector->Append("Medium");
  prebuilt_selector->Append("Hard");
  prebuilt_selector->Append("Expert");
  prebuilt_selector->Select(0);

  wxButton* load_prebuilt_btn
  = new wxButton(this, 12001, "Load Pre-Built"); //TODO: center align the button


  main_box->Add(grid, 9, wxEXPAND | wxALL);
  main_box->Add(m_btn, 1);
  main_box->Add(prebuilt_selector, 1);
  main_box->Add(load_prebuilt_btn, 1);

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

std::map<std::string, std::string> prebuilt_map{
    {"Easy", "../../../../more_examples/easy_1.txt"},
    {"Medium", "../../../../more_examples/medium_1.txt"},
    {"Hard", "../../../../more_examples/hard_1.txt"},
    {"Expert", "../../../../more_examples/expert_1.txt"},
};

void cMain::on_load_prebuilt_clicked(wxCommandEvent &evt) {

//TODO: Get the combobox to work
   // wxString selection{ prebuilt_selector->GetValue() };
   // std::string prebuilt_file{prebuilt_map[(std::string)selection]};
    std::string prebuilt_file{ prebuilt_map["Expert"] };

    load_prebuilt(prebuilt_file);
    print_sudoku();
    evt.Skip();
}

void cMain::on_solve_clicked(wxCommandEvent &evt) {
  read_sudoku();
  solve();
  evt.Skip();
}

cMain::~cMain() { delete[] elements; }
