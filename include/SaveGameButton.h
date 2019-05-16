#ifndef SHINY_SPORK_SAVEGAMEBUTTON_H
#define SHINY_SPORK_SAVEGAMEBUTTON_H

#include "Button.h"

class SaveGameButton : public Button {
 public:
  explicit SaveGameButton(State&, int, int);

  void Click(int, int) override;
};

#endif //SHINY_SPORK_SAVEGAMEBUTTON_H
