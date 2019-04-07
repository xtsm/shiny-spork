#ifndef INCLUDE_LOADGAMEBUTTON_H_
#define INCLUDE_LOADGAMEBUTTON_H_
#include <memory>
#include "Button.h"

class LoadGameButton : public Button {
 public:
  explicit LoadGameButton(State&, int, int);

  void Click() override;
};

#endif  // INCLUDE_LOADGAMEBUTTON_H_
