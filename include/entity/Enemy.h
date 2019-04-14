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
  Enemy(const std::string& path, double x, double y,
        const Tile& current_tile, const Direction& direction_of_move,
        State& state, int priority);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void DoMove();

  void DecreaseHealth(int delta);
  void EncreaseHealth(int delta);

  void DoDamage(Enemy& other_entity);

  bool IsAlive() const { return is_alive_; }

 private:
  std::string name_;
  int frames_;
  Tile current_tile_;
  Direction direction_of_move_;
  Tile desination_tile_;
  int max_health_;
  int health_;
  sf::RectangleShape health_bar_;
  sf::RectangleShape damage_bar_;
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

  explicit EnemyCreator(State&);

  void Load(const std::string&);

  void LoadSpawnPointsAndDirections(const std::string& path_to_file);

  void CreateSomeEnemies(int64_t count);

 private:
  State& state_;
  std::vector<std::pair<Point, Direction>> spawn_points_;
  std::vector<std::string> enemy_types_;

  int GetHealthFromType(const EnemyType& type);
  double GetSpeedByType(const EnemyType& type);
};

#endif //SHINY_SPORK_ENEMY_H