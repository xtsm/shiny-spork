#ifndef SHINY_SPORK_UPDATETOWERBUTTON_H
#define SHINY_SPORK_UPDATETOWERBUTTON_H

#include "Button.h"
#include "Tower.h"

class UpdateTowerButton : public Button {
 public:
  explicit UpdateTowerButton(State&, int, int, Tower&);

  void Click() override;

 private:
  Tower& tower_;
};

#endif //SHINY_SPORK_UPDATETOWERBUTTON_H
