#pragma once
#include "Button.hpp"
#include <memory>

class ExitButton : public Button {
 public:
  explicit ExitButton(State&, int, int);

  void Click() override;
};
