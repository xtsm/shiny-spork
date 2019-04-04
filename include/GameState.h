#ifndef INCLUDE_GAMESTATE_H_
#define INCLUDE_GAMESTATE_H_

#include <string>
#include <iostream>
#include "State.h"
#include "Background.h"
#include "Tower.h"
#include "BuildButton.h"

class GameState: public State {
 public:
  explicit GameState(StateManager& states);
  void Load(const std::string& file_name);

  void Tick() override;
  void ProcessEvent(sf::Event&) override;

  void BuildTower(std::string&& tower_path, int x, int y);
  void BuildMenu();

 protected:
  int width_, height_;
  Background background_, panel_side_;
  BuildButton build_button;
};

#endif  // INCLUDE_GAMESTATE_H_
