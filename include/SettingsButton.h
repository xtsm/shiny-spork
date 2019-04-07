#ifndef INCLUDE_SETTINGSBUTTON_H_
#define INCLUDE_SETTINGSBUTTON_H_

#include <memory>
#include "Button.h"

class SettingsButton : public Button {
 public:
  explicit SettingsButton(State&, int, int);

  void Click() override;
};

#endif  // INCLUDE_SETTINGSBUTTON_H_
