#ifndef INCLUDE_GAMESTATE_H_
#define INCLUDE_GAMESTATE_H_
#include <string>
#include "State.h"
#include "Background.h"
#include "PauseButton.h"
#include "utility/Map.h"
#include "ContinueButton.h"

class GameState: public State {
 public:
  GameState(StateManager& states, const Map& map);
  void Load(std::string file_name);
  void Pause();
  void Tick() override;
  void ProcessEvent(sf::Event&) override;
  Map GetMap() const { return map_; }

 protected:
  int width_, height_;
  Background background_, panel_side_;
  PauseButton pause_;
  Map map_;
};

#endif  // INCLUDE_GAMESTATE_H_
