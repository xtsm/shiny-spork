
#include <entity/Entity.h>
#include <State.h>

#include "entity/Entity.h"


Entity::Entity(double health, double power, double x, double y,
               const std::shared_ptr<State>& state, const DrawPriority& priority)
    : Widget(*state, priority), health_(health), power_(power),
      is_alive_(true), position_({x, y}) {}

void Entity::LoadSprite(const std::string& file_name) {
  sprite_.setTexture(State::GetTextureResourceManager().GetOrLoadResource(file_name));
}
