#ifndef SHINY_SPORK_MAINMENUBUTTON_H
#define SHINY_SPORK_MAINMENUBUTTON_H

#include <memory>
#include "Button.h"

class MainMenuButton : public Button {
 public:
  explicit MainMenuButton(State&, int, int);

  void Click() override;
};

#endif //SHINY_SPORK_MAINMENUBUTTON_H
