#ifndef INCLUDE_GAMESTATE_H_
#define INCLUDE_GAMESTATE_H_
#include <string>
#include "State.h"
#include "Background.h"
#include "PauseButton.h"
#include "ContinueButton.h"

class GameState: public State {
 public:
  explicit GameState(StateManager& states);
  void Load(std::string file_name);
  void Pause();
  void Tick() override;
  void ProcessEvent(sf::Event&) override;

 protected:
  int width_, height_;
  Background background_, panel_side_;
  PauseButton pause_;
};

#endif  // INCLUDE_GAMESTATE_H_
