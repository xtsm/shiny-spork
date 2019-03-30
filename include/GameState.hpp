#ifndef SHINY_SPORK_GAMESTATE_HPP
#define SHINY_SPORK_GAMESTATE_HPP
#include <State.hpp>

class GameState: public State {
 public:
  GameState(StateManager& states);
  void Load(sf::String file_name);

  void Tick();
  void ProcessEvent(sf::Event&);

 protected:
  int width_, height_;
  sf::Texture background_;
};
#endif //SHINY_SPORK_GAMESTATE_HPP
