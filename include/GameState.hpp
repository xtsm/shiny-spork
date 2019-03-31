#ifndef SHINY_SPORK_GAMESTATE_HPP
#define SHINY_SPORK_GAMESTATE_HPP
#include <State.hpp>
#include <Background.hpp>

class GameState: public State {
 public:
  explicit GameState(StateManager& states);
  void Load(std::string file_name);

  void Tick() override;
  void ProcessEvent(sf::Event&) override;

 protected:
  int width_, height_;
  Background background_, panel_side_;
};
#endif //SHINY_SPORK_GAMESTATE_HPP
