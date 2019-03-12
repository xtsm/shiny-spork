
#include <ExitButton.hpp>
#include <iostream>

void ExitButton::Click() {
  std::cout << "Close" << std::endl;
  parent_.close();
}

void ExitButton::MouseOut() {
  Button::MouseOut();
}

void ExitButton::MouseIn() {
  Button::MouseIn();
}

ExitButton::ExitButton(State& state, int x, int y, const sf::String& title,
                       sf::RenderWindow& parent)
    : Button(state, x, y, title), parent_(parent) {}


