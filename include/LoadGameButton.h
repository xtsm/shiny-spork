#ifndef SHINY_SPORK_LOADGAMEBUTTON_H
#define SHINY_SPORK_LOADGAMEBUTTON_H
#include <memory>
#include "Button.h"

class LoadGameButton : public Button {
 public:
  explicit LoadGameButton(State&, int, int);

  void Click() override;
};

#endif //SHINY_SPORK_LOADGAMEBUTTON_H
