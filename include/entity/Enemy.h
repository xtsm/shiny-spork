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

  void Click(int, int) override;

  void DoDamage(Enemy& other_entity);

  std::vector<sf::Text> GetInfo() const override;

  std::string GetName() const;
  int GetHealth() const;
  int GetMaxHealth() const;
  int GetPower() const;

 private:
  std::string name_;
  int frames_;
  sf::IntRect current_sprite_rect_;
  int max_delay_for_sprite_change_;
  int delay_for_sprite_change_;
  Tile current_tile_;
  Direction direction_of_move_;
  Tile destination_tile_;
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
  void ChangeCurrentSpriteRect();
  void CheckAndChangeCoordinates();
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