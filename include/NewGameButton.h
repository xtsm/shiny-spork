#ifndef INCLUDE_NEWGAMEBUTTON_H_
#define INCLUDE_NEWGAMEBUTTON_H_
#include <memory>
#include "Button.h"

class NewGameButton : public Button {
 public:
  explicit NewGameButton(State&, int, int);

  void Click(int, int) override;
};

#endif  // INCLUDE_NEWGAMEBUTTON_H_
