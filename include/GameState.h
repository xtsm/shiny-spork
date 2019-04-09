#ifndef INCLUDE_GAMESTATE_H_
#define INCLUDE_GAMESTATE_H_

#include <string>
#include <iostream>
#include <memory>
#include "State.h"
#include "Background.h"
#include "Tower.h"
#include "BuildButton.h"
#include "PauseButton.h"
#include "BuildMenuGrid.h"

class GameState: public State {
 public:
  explicit GameState(StateManager&);
  void Load(const std::string&);
  void Pause();
  void Tick() override;
  void ProcessEvent(sf::Event&) override;

  // Строит башню с характеристиками из файла
  void BuildTower(const std::string&, int, int);
  // Вызывает меню постройки башни
  void LoadBuildMenu(const std::string&, const sf::Sprite& tower_tex);
  // Создаёт меню информации для башни
  void InfoMenuForTower(long long);
  //Удаляет башню
  void RemoveTower(const std::shared_ptr<Tower>&);
  //Удаляет меню постройки
  void RemoveBuildMenu();
  //Удаляет меню информации
  void RemoveInfoMenu();
  //Проверяет свободна ли клетка
  bool IsFree(int, int) const;

 protected:
  std::shared_ptr<Background> background_ptr_, panel_side_ptr_;
  std::shared_ptr<BuildButton> build_button_ptr_;
  std::shared_ptr<PauseButton> pause_button_ptr_;
  std::shared_ptr<BuildMenuGrid> build_menu_grid_ptr_;
  std::map<long long, std::shared_ptr<Tower>> towers_;
  std::map<long long, std::shared_ptr<Widget>> info_menu_;
  bool is_free[10][10];
};

#endif  // INCLUDE_GAMESTATE_H_
