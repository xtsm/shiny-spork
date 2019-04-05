#ifndef SHINY_SPORK_BUILDBUTTON_H
#define SHINY_SPORK_BUILDBUTTON_H

#include "Button.h"

class BuildButton : public Button {
 public:
  explicit BuildButton(State&, int, int);

  void Click() override;

 private:
  State& state_;
};

#endif //SHINY_SPORK_BUILDBUTTON_H
