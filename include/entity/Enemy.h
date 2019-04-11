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
  Enemy(double health, int speed, double x, double y,
        State& state, const DrawPriority& priority);

  void DoMove();

  void DecreaseHealth(double delta);
  void EncreaseHealth(double delta);

  void DoDamage(Enemy& other_entity);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

//  void SetTexture(const sf::Texture& texture) {}
// Use textures_resource_manager instead

 private:
  Direction move_direction_;
  double health_;
  int speed_;
  int power_;
  Point position_;
  bool is_alive_;
  void DoMove(const Direction& direction);
};

class EnemyCreator {
 public:
  EnemyCreator() = default;

  explicit EnemyCreator(State& state);

  void LoadSpawnPoints(const std::string& path_to_file);

  void CreateSomeEnemies(int64_t count);

 private:
  State& state_;
  std::vector<Point> spawn_points_;

  int GetHealthFromType(const EnemyHealthType& type);
  double GetSpeedByType(const EnemyHealthType& type);
};

#endif //SHINY_SPORK_ENEMY_H