#ifndef SHINY_SPORK_CHANGELEVELBUTTON_H
#define SHINY_SPORK_CHANGELEVELBUTTON_H

#include "Button.h"

class ChangeLevelButton : public Button {
 public:
  explicit ChangeLevelButton(State& state);

  void Click(int x, int y) override;
};

#endif //SHINY_SPORK_CHANGELEVELBUTTON_H
