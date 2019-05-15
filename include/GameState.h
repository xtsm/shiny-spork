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
#include "entity/Base.h"
#include "StartGameButton.h"
#include "BuildButton.h"
#include "PauseButton.h"
#include "BuildMenuGrid.h"
#include "utility/Map.h"
#include "ContinueButton.h"
#include "UpdateTowerButton.h"
#include "RemoveTowerButton.h"
#include "EntityInfo.h"
#include "BalanceLabel.h"

class GameState: public State {
 public:
  explicit GameState(StateManager& states);
  void SaveGame();
  void LoadSave();
  void Load();
  void Pause();
  void Tick() override;
  void ProcessEvent(sf::Event&) override;
  std::shared_ptr<Map> GetMap() const { return map_ptr_; }
  std::shared_ptr<Base> GetBase() const { return base_ptr_; }
  // Строит башню с характеристиками из файла
  void BuildTower(const std::string&, int, int);
  // Вызывает меню постройки башни
  void LoadBuildMenu(const std::string&, const sf::Sprite&, int);
  // Создаёт меню информации для башни
  void InfoMenuForTower(int64_t id);
  // Отображает информацию о враге
  void InfoMenuForEnemy(int64_t id);
  // Отображает информацию о базе
  void InfoMenuForBase();
  //Удаляет башню
  void RemoveTower(const std::shared_ptr<Tower>&);
  //Удаляет меню постройки
  void RemoveBuildMenu();
  //Удаляет меню информации
  void RemoveInfoMenu();
  //Проверяет свободна ли клетка
  bool IsFree(int, int) const;
  void SetIsFree(int, int, bool);
  //Создаёт Projectile летящий в цель
  void AddProjectile(const std::shared_ptr<Projectile>& projectile);
  //Удаляет из очереди отрисовки
  void RemoveProjectile(int64_t id);
  //Находит цель для башни
  std::shared_ptr<Enemy> FindAim(int, int, int);
  std::vector<std::shared_ptr<Enemy>> GetEnemiesInRange(int, int, int);
  // Устанавливает флаг начала волн врагов
  void SetProducing(bool produce);
  // Удаляет кнопку Start Game с поля
  void RemoveStartButton();
  // Возвращает количество врагов
  int64_t GetAmountOfEnemies() const;
  // Создаёт count врагов
  void CreateSomeEnemies(int count);
  // Добавляет врага на карту
  void AddNewEnemy(const std::string&, double, double,
                   const Direction& move_direction);
  void ChangeEnemyPriority(long long id, DrawPriority new_priority);
  // Удаляет врага с карты
  void RemoveEnemyById(int64_t id);
  //Возвращает баланс
  int GetBalance() const;
  //Изменяет баланс на delta
  void ChangeBalance(int delta);
  bool IsIncrementLevelIsAvailable() const;
  // Переходит на следующий уровень, если level_number + 1 <= max_level_number_
  void IncrementLevel();
  void SetAmountOfWaves(int amount);
  void SetAmountOfEnemiesPerWave(int amount);
  int GetAmountOfWaves() const;
  int GetAmountOfEnemiesPerWave() const;

  void GameOver();

  void StartGame();

  int64_t GetTime() const;

  std::shared_ptr<Enemy> GetEnemyByID(int64_t id);

 protected:
  int width_, height_;
  std::shared_ptr<Background> background_ptr_, panel_side_ptr_;
  std::vector<std::shared_ptr<BuildButton>> build_button_ptrs_;
  std::shared_ptr<PauseButton> pause_button_ptr_;
  std::shared_ptr<UpdateTowerButton> update_tower_button_ptr_;
  std::shared_ptr<RemoveTowerButton> remove_tower_button_ptr_;
  std::shared_ptr<StartGameButton> start_game_button_ptr_;
  std::shared_ptr<BuildMenuGrid> build_menu_grid_ptr_;
  std::shared_ptr<Map> map_ptr_;
  std::shared_ptr<EntityInfo> info_;
  std::shared_ptr<BalanceLabel> balance_ptr_;
  std::shared_ptr<Tower> image_tower_ptr_;
  std::map<int64_t, std::shared_ptr<Tower>> towers_;
  std::map<int64_t, std::shared_ptr<Projectile>> projectiles_;
  std::map<int64_t, std::shared_ptr<Enemy>> enemies_;
  std::shared_ptr<Base> base_ptr_;
  EnemyCreator creator_of_enemies_;
  bool is_enemies_produce_;
  // Задержка между спавном врагов
  int current_delay_;
  int delay_;
  bool is_info_displayed_;
  std::string level_path_;
  int level_number_;
  int max_level_number_;
  int amount_of_waves_for_level_;
  int amount_of_enemies_for_wave_;
  int64_t timer_;
  bool is_level_end_;
  bool is_game_end_;
  bool is_game_started_;
};

#endif  // INCLUDE_GAMESTATE_H_
