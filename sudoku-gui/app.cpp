#include "app.hpp"

wxIMPLEMENT_APP(App);

App::App() {}

App::~App() {}

bool App::OnInit() {
  m_frame1 = new cMain();
  m_frame1->Show();

  return true;
}
