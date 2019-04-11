#include <State.h>
#include "entity/Entity.h"

Entity::Entity(State& state, const DrawPriority& priority)
    : Widget(state, priority), is_info_(false) {}

void Entity::LoadSprite(const std::string& file_name) {
  sprite_.setTexture(State::GetTextureResourceManager().GetOrLoadResource(file_name));
}

void Entity::SetInfo(bool value) {
  is_info_ = value;
}

