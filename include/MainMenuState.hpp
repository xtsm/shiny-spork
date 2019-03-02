#pragma once
#include <State.hpp>

class MainMenuState: public State {
 public:
  MainMenuState(StateManager& states);
  void Tick();
  void Draw(sf::RenderTarget &target);
  void ProcessEvent(sf::Event &event);
};
