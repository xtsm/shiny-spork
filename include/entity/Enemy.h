#pragma once

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
  Enemy(double health, int x, int y,
      std::shared_ptr<State>& state, DrawPriority& priority);

  void DoMove() final;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const final;

  ResourceManager<sf::Sprite> GetSpriteManager() const { return sprites_manager_; }
//  void SetTexture(const sf::Texture& texture) {}
// Use textures_resource_manager instead

 private:

  void DoMove(const Direction& direction);
};

class EnemyCreator {
 public:
  explicit EnemyCreator(const std::shared_ptr<State>& state);

  void LoadSpawnPoints(const std::string& path_to_file);

  void CreateSomeEnemies(int64_t count);

 private:
  std::shared_ptr<State> state_;
  std::vector<Point> spawn_points_;
  static const DrawPriority enemy_priority_;

  int GetHealthFromType(const EnemyHealthType& type);
};
