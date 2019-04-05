#ifndef SHINY_SPORK_BUILDBUTTON_H
#define SHINY_SPORK_BUILDBUTTON_H

#include "Button.h"

class BuildButton : public Button {
 public:
  explicit BuildButton(State&, int, int, const std::string&);

  void Click() override;

 private:
  std::string source_;
};

#endif //SHINY_SPORK_BUILDBUTTON_H
