#ifndef SHINY_SPORK_ENEMY_H
#define SHINY_SPORK_ENEMY_H

#include "entity/Entity.h"
#include "utility/ResourceManager.h"
#include "utility/Direction.h"
#include <SFML/Graphics.hpp>
#include "State.h"
#include "utility/Point.h"
#include "utility/Map.h"
#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <random>

enum class EnemyType {
  VeryHigh,
  High,
  Middle,
  Low
};

class Enemy : public Entity {
 public:
  Enemy(double health, double speed, double x, double y,
        const Tile& current_tile, const Direction& direction_of_move,
        State& state, int priority);

  void DoMove();

  void DecreaseHealth(double delta);
  void EncreaseHealth(double delta);

  void DoDamage(Enemy& other_entity);

  bool IsAlive() const { return is_alive_; }

 private:
  Tile current_tile_;
  Direction direction_of_move_;
  Tile desination_tile_;
  double health_;
  double speed_;
  int power_;
  Point position_;
  bool is_alive_;
  void DoMove(const Direction& direction);
  void ChangeDirectionTile(const Tile& new_direction_tile);
  std::vector<std::pair<Tile, Direction>> GetAvailableMoves(int x, int y) const;
//  bool IsMoveHasChangedTile(const Tile& tile_after_move);
};

class EnemyCreator {
 public:
  explicit EnemyCreator(State& state);

  void LoadSpawnPointsAndDirections(const std::string& path_to_file);

  void CreateSomeEnemies(int64_t count);

 private:
  State& state_;
  std::vector<std::pair<Point, Direction>> spawn_points_;

  int GetHealthFromType(const EnemyType& type);
  double GetSpeedByType(const EnemyType& type);
};

#endif //SHINY_SPORK_ENEMY_H