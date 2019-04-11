#ifndef INCLUDE_GAMESTATE_H_
#define INCLUDE_GAMESTATE_H_

#include <string>
#include <iostream>
#include <cstdint>
#include <memory>
#include "State.h"
#include "entity/Enemy.h"
#include "Background.h"
#include "entity/Tower.h"
#include "BuildButton.h"
#include "PauseButton.h"
#include "BuildMenuGrid.h"
#include "utility/Map.h"
#include "ContinueButton.h"
#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"

class GameState: public State {
 public:
  explicit GameState(StateManager& states);
  void Load(const std::string&);
  void Pause();
  void Tick() override;
  void ProcessEvent(sf::Event&) override;
  std::shared_ptr<Map> GetMap() const { return map_ptr_; }
  // Строит башню с характеристиками из файла
  void BuildTower(const std::string&, int, int);
  // Вызывает меню постройки башни
  void LoadBuildMenu(const std::string&, const sf::Sprite& tower_tex);
  // Создаёт меню информации для башни
  void InfoMenuForTower(int64_t id);
  //Удаляет башню
  void RemoveTower(const std::shared_ptr<Tower>&);
  //Удаляет меню постройки
  void RemoveBuildMenu();
  //Удаляет меню информации
  void RemoveInfoMenu();
  //Проверяет свободна ли клетка
  bool IsFree(int, int) const;
  //Удаляет из очереди отрисовки
  void RemoveProjectile(int64_t id);
  int64_t GetAmountOfEnemies() const;
  void AddNewEnemy(const Enemy&);

 protected:
  int width_, height_;
  std::shared_ptr<Background> background_ptr_, panel_side_ptr_;
  std::shared_ptr<BuildButton> build_button_ptr_;
  std::shared_ptr<PauseButton> pause_button_ptr_;
  std::shared_ptr<UpdateTowerButton> update_tower_button_ptr_;
  std::shared_ptr<RemoveTowerButton> remove_tower_button_ptr_;
  std::shared_ptr<BuildMenuGrid> build_menu_grid_ptr_;
  std::shared_ptr<Map> map_ptr_;
  std::shared_ptr<Entity> info_menu_;
  std::map<int64_t, std::shared_ptr<Tower>> towers_;
  std::map<int64_t, std::shared_ptr<Projectile>> projectiles_;
  std::map<int64_t, std::shared_ptr<Enemy>> enemies_;
  EnemyCreator creator_of_enemies_;
};

#endif  // INCLUDE_GAMESTATE_H_
