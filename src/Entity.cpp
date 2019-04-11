#include "entity/Entity.h"

Entity::Entity(State& state, const DrawPriority& priority)
    : Widget(state, priority), is_info_(false) {}

void Entity::SetInfo(bool value) {
  is_info_ = value;
}
