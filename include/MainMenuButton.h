#ifndef INCLUDE_MAINMENUBUTTON_H_
#define INCLUDE_MAINMENUBUTTON_H_

#include <memory>
#include "Button.h"

class MainMenuButton : public Button {
 public:
  explicit MainMenuButton(State&, int, int);

  void Click() override;
};

#endif  // INCLUDE_MAINMENUBUTTON_H_
