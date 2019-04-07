#ifndef SHINY_SPORK_PAUSEBUTTON_H
#define SHINY_SPORK_PAUSEBUTTON_H

#include "Button.h"
#include "State.h"

class PauseButton : public Button {
 public:
  PauseButton(State& state, int x, int y);
  void Click() final;
};

#endif //SHINY_SPORK_PAUSEBUTTON_H
