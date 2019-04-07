#ifndef INCLUDE_PAUSEBUTTON_H_
#define INCLUDE_PAUSEBUTTON_H_

#include "Button.h"
#include "State.h"

class PauseButton : public Button {
 public:
  PauseButton(State& state, int x, int y);
  void Click() final;
};

#endif  // INCLUDE_PAUSEBUTTON_H_
