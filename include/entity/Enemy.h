#ifndef SHINY_SPORK_ENEMY_H
#define SHINY_SPORK_ENEMY_H

#include "entity/Entity.h"
#include "utility/ResourceManager.h"
#include "utility/Direction.h"
#include <SFML/Graphics.hpp>
#include "State.h"
#include "utility/Point.h"
#include <memory>
#include <utility>
#include <string>
#include <vector>
#include <random>

enum class EnemyHealthType {
  VeryHigh,
  High,
  Middle,
  Low
};

class Enemy : public Entity {
 public:
  Enemy(double health, double speed, double x, double y,
        const Direction& move_direction, State& state, int priority);

  void DoMove();

  void DecreaseHealth(double delta);
  void EncreaseHealth(double delta);

  void DoDamage(Enemy& other_entity);

  bool IsAlive() const { return is_alive_; }

 private:
  Direction move_direction_;
  double health_;
  double speed_;
  int power_;
  Point position_;
  bool is_alive_;
  void DoMove(const Direction& direction);

  std::vector<Direction> GetAvailableMoves(int x, int y) const;
};

class EnemyCreator {
 public:
  explicit EnemyCreator(State& state);

  void LoadSpawnPointsAndDirections(const std::string& path_to_file);

  void CreateSomeEnemies(int64_t count);

 private:
  State& state_;
  std::vector<std::pair<Point, Direction>> spawn_points_;

  int GetHealthFromType(const EnemyHealthType& type);
  double GetSpeedByType(const EnemyHealthType& type);
};

#endif //SHINY_SPORK_ENEMY_H