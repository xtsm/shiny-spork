#ifndef INCLUDE_UPDATETOWERBUTTON_H_
#define INCLUDE_UPDATETOWERBUTTON_H_

#include "Button.h"
#include "Tower.h"

class UpdateTowerButton : public Button {
 public:
  explicit UpdateTowerButton(State&, int, int, Tower&);

  void Click() override;

 private:
  Tower& tower_;
};

#endif  // INCLUDE_UPDATETOWERBUTTON_H_
