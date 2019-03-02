#pragma once
#include <SFML/Graphics.hpp>
#include <State.hpp>

class Widget{
 public:
  explicit Widget(State& state);
  virtual void ProcessEvent(sf::Event& event)  = 0;
 protected:
  State& state;
};