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
  explicit GameState(StateManager&);
  void Load(const std::string&);

  void Tick() override;
  void ProcessEvent(sf::Event&) override;

  //Строит башню с характеристиками из файла
  void BuildTower(const std::string&, int, int);
  //Вызывает меню постройки башни
  void BuildMenu(const std::string&);
  //Создаёт меню информации для башни
  void InfoMenuForTower(Tower&);

 protected:
  int width_, height_;
  std::shared_ptr<Background> background_ptr_, panel_side_ptr_;
  std::shared_ptr<BuildButton> build_button_ptr_;
};

#endif  // INCLUDE_GAMESTATE_H_
