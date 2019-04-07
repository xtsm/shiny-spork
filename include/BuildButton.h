#ifndef INCLUDE_BUILDBUTTON_H_
#define INCLUDE_BUILDBUTTON_H_

#include "Button.h"
#include <string>

class BuildButton : public Button {
 public:
  explicit BuildButton(State&, int, int, const std::string&);

  void Click() override;

 private:
  std::string source_;
};

#endif  // INCLUDE_BUILDBUTTON_H_
