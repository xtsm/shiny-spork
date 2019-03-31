#ifndef INCLUDE_EXITBUTTON_H_
#define INCLUDE_EXITBUTTON_H_
#include <memory>
#include "Button.h"

class ExitButton : public Button {
 public:
  explicit ExitButton(State&, int, int);

  void Click() override;
};

#endif  // INCLUDE_EXITBUTTON_H_
