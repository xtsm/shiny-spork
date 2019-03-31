#ifndef SHINY_SPORK_SETTINGSBUTTON_H
#define SHINY_SPORK_SETTINGSBUTTON_H

#include <memory>
#include "Button.h"

class SettingsButton : public Button {
 public:
  explicit SettingsButton(State&, int, int);

  void Click() override;
};

#endif //SHINY_SPORK_SETTINGSBUTTON_H
