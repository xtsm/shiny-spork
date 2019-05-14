#include <State.h>
#include <StateManager.h>
#include "entity/Entity.h"
#include "GameState.h"

Entity::Entity(State& state, const DrawPriority& priority)
    : Entity(state, priority, 0, 0) {}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(sprite_, states);
}

void Entity::Click(int, int) {
  StateManager& states = state_.GetStateManager();
  states.game_ptr_->RemoveInfoMenu();
}

void Entity::MouseIn(int, int) {
  if (clicked_) {
    sprite_.setColor(sf::Color(255, 0, 255));
  } else {
    sprite_.setColor(sf::Color(200, 200, 255));
  }
  is_mouse_in_ = true;
}

void Entity::MouseOut(int, int) {
  sprite_.setColor(default_sprite_color_);
  is_mouse_in_ = false;
}

bool Entity::PointCheck(int x, int y) const {
  return sprite_.getGlobalBounds().contains(x, y);
}

void Entity::LoadSprite(const std::string& file_name) {
  sprite_.setTexture(State::GetTextureResourceManager().GetOrLoadResource(file_name), true);
  icon_sprite_.setTexture(State::GetTextureResourceManager().GetOrLoadResource(file_name));
}

void Entity::SetInfo(bool value) {
  if (value) {
    default_sprite_color_ = sf::Color(200, 200, 255);
    sprite_.setColor(default_sprite_color_);
  } else {
    default_sprite_color_ = sf::Color(255, 255, 255);
    sprite_.setColor(default_sprite_color_);
  }
  is_info_ = value;
}

sf::Sprite Entity::GetIconSprite() const {
  return icon_sprite_;
}

std::vector<sf::Text> Entity::GetInfo() const {
  return std::vector<sf::Text>();
}

void Entity::InitText(sf::Text& text, int x, int y,
                      int character_size, sf::Color color) const {
  const sf::Font& font_ =
      State::GetFontResourceManager().GetOrLoadResource("assets/font/default.ttf");
  text.setFont(font_);
  text.setFillColor(color);
  text.setOutlineColor(sf::Color::White);
  text.setCharacterSize(static_cast<unsigned int>(character_size));
  text.move(x, y);
}

double Entity::GetCenterX() const {
  return x_ + sprite_.getGlobalBounds().width / 2;
}

double Entity::GetCenterY() const {
  return y_ + sprite_.getGlobalBounds().height / 2;
}

void Entity::SetSpriteCenter(double x, double y) {
  sprite_.setPosition(x - sprite_.getGlobalBounds().width / 2, y - sprite_.getGlobalBounds().height / 2);
}

void Entity::DecreaseHealth(int delta) {
  if (health_ > 0 && health_ - delta >= 0) {
    health_ -= delta;
  } else {
    health_ = 0;
  }
  health_bar_.setSize(sf::Vector2f(static_cast<float>(health_) / max_health_ * 30, 3));
}

Entity::Entity(State& state, const DrawPriority& priority, int health, int max_health)
    : Widget(state, priority),
      max_health_(max_health),
      health_(health),
      health_bar_(),
      damage_bar_(),
      sprite_(),
      icon_sprite_(),
      default_sprite_color_(sf::Color(255, 255, 255)),
      is_mouse_in_(false),
      is_info_(false),
      sound_of_entity_() {}

void Entity::Save(std::ostream&) {}
