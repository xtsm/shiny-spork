#pragma once
#include "Button.hpp"
#include <memory>

class ExitButton : public Button {
 public:
  explicit ExitButton(State&, int, int, const sf::String&,
                      sf::RenderWindow&);

  void Click() override;
  void MouseIn() override;
  void MouseOut() override;

 private:
  sf::RenderWindow& parent_;
};
