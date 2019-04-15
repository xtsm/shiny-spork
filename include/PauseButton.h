#ifndef INCLUDE_PAUSEBUTTON_H_
#define INCLUDE_PAUSEBUTTON_H_

#include "Button.h"
#include "State.h"

class PauseButton : public Button {
 public:
  PauseButton(State&, int, int);

  void Click(int, int) final;
};

#endif  // INCLUDE_PAUSEBUTTON_H_
