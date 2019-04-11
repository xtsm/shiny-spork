#include <State.h>
#include <StateManager.h>
#include "entity/Entity.h"
#include "GameState.h"

Entity::Entity(State& state, const DrawPriority& priority)
    : Widget(state, priority), state_(state), is_info_(false) {}

void Entity::LoadSprite(const std::string& file_name) {
  sprite_.setTexture(State::GetTextureResourceManager().GetOrLoadResource(file_name));
}

void Entity::SetInfo(bool value) {
  is_info_ = value;
}

