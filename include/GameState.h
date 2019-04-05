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
  std::shared_ptr<Background> background_ptr_, panel_side_ptr_;
  std::shared_ptr<BuildButton> build_button_ptr_;
};

#endif  // INCLUDE_GAMESTATE_H_
