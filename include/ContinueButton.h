#ifndef INCLUDE_CONTINUEBUTTON_H_
#define INCLUDE_CONTINUEBUTTON_H_

#include "Button.h"

class ContinueButton : public Button {
 public:
  explicit ContinueButton(State&, int, int);

  void Click(int, int) override;
};

#endif  // INCLUDE_CONTINUEBUTTON_H_
