#pragma once
#include <SFML/Graphics.hpp>

class StateManager;

class State {
 public:
  State(StateManager& states);
  virtual void Tick() = 0;
  virtual void Draw(sf::RenderTarget &target) = 0;
  virtual void ProcessEvents(sf::Window &wnd) = 0;
 protected:
  StateManager& states;
};
