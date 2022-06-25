#pragma once

#include "cMain.hpp"
#include "wx/wx.h"

class App : public wxApp {

public:
  App();
  ~App();

  virtual bool OnInit();

private:
  cMain *m_frame1 = nullptr;
};
