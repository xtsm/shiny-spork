
#include <EntityInfo.h>

#include "EntityInfo.h"

EntityInfo::EntityInfo(State& state)
    : Widget(state, DrawPriority(1005, this)),
      entity_(),
      amount_of_lines_(0),
      max_amount_of_lines_(6) {
}

void EntityInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  if (entity_ == nullptr) {
    return;
  }
  sf::Sprite image_of_entity_ = entity_->GetIconSprite();
  std::vector<sf::Text> some_info_about_entity_ = entity_->GetInfo();
  target.draw(image_of_entity_, states);
  for (const auto& text : some_info_about_entity_) {
    target.draw(text, states);
  }
}

void EntityInfo::Clear() {
  if (entity_ != nullptr) {
    entity_->SetInfo(false);
  }
  entity_ = nullptr;
}

void EntityInfo::ChangeEntity(const std::shared_ptr<Entity>& entity) {
  Clear();
  if (entity == nullptr) {
    return;
  }
  entity_ = entity;
  entity_->SetInfo(true);
}

int64_t EntityInfo::GetEntityID() const {
  if (entity_ == nullptr) {
    return -1;
  } else {
    return entity_->GetID();
  }
}
