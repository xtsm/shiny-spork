#ifndef INCLUDE_GAMESTATE_H_
#define INCLUDE_GAMESTATE_H_
#include <string>
#include "State.h"
#include "Background.h"

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

#endif  // INCLUDE_GAMESTATE_H_