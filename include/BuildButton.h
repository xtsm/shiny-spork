#ifndef INCLUDE_BUILDBUTTON_H_
#define INCLUDE_BUILDBUTTON_H_

#include "Button.h"
#include <string>

class BuildButton : public Button {
 public:
  explicit BuildButton(State&, int, int, const std::string&, const std::string&);

  void Click(int, int) override;

 private:
  std::string source_;
  sf::Sprite tower_sprite_;
};

#endif  // INCLUDE_BUILDBUTTON_H_
