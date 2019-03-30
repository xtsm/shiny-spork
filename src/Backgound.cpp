#include "Backgound.hpp"

Background::Background(State& state) :
    Widget(state, DrawPriority(3, this)),
    bg_(),
    bg_sprite_() {
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
}

void Background::LoadFromFile(const std::string& file_name) {
  bg_.loadFromFile(file_name);
  bg_sprite_.setTexture(bg_);
}
