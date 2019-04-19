#ifndef SHINY_SPORK_INFO_H
#define SHINY_SPORK_INFO_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <entity/Entity.h>

#include "Widget.h"

class EntityInfo : public Widget {
 public:
  explicit EntityInfo(State&);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void Clear();

  void ChangeEntity(const std::shared_ptr<Entity>& entity);

  int64_t GetEntityID() const;

 private:
  std::shared_ptr<Entity> entity_;
  int amount_of_lines_;
  const int max_amount_of_lines_;
};

#endif //SHINY_SPORK_INFO_H
