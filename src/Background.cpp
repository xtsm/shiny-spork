#include "Background.h"
#include "StateManager.h"
#include <string>

Background::Background(State& state, int priority) :
    Widget(state, DrawPriority(priority, this)),
    bg_sprite_() {
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
}

void Background::Click(int, int) {
  std::shared_ptr<GameState> game_ptr = state_.GetStateManager().game_ptr_;
  game_ptr->RemoveInfoMenu();
  game_ptr->RemoveBuildMenu();
}

bool Background::PointCheck(int x, int y) const {
  return bg_sprite_.getGlobalBounds().contains(x, y);
}

void Background::SetSize(int w, int h) {
  bg_sprite_.setTextureRect(sf::Rect<int>(0, 0, w, h));
}

void Background::SetPosition(int x, int y) {
  Widget::SetPosition(x, y);
  bg_sprite_.setPosition(x, y);
}

void Background::LoadFromFile(const std::string& file_name) {
  sf::Texture& bg_ = State::GetTextureResourceManager().GetOrLoadResource(file_name);
  bg_.setRepeated(true);
  bg_sprite_.setTexture(bg_);
}

void Background::SetDim(bool value) {
  if (value) {
    bg_sprite_.setColor(sf::Color(120, 120, 120));
  } else {
    bg_sprite_.setColor(sf::Color(255, 255, 255));
  }
}

void Background::LoadFromTexture(const sf::Texture& texture) {
  bg_sprite_.setTexture(texture);
}