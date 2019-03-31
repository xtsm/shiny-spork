#include "Backgound.hpp"

Background::Background(State& state) :
    Widget(state, DrawPriority(5, this)),
    bg_(),
    bg_sprite_() {
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
}

void Background::SetSize(int w, int h) {
  bg_sprite_.setTextureRect(sf::Rect<int>(0,0,w,h));
}

void Background::SetPosition(int x,int y) {
  Widget::SetPosition(x,y);
  bg_sprite_.setPosition(x,y);
}

void Background::LoadFromFile(const std::string& file_name) {
  bg_.loadFromFile(file_name);
  bg_.setRepeated(true);
  bg_sprite_.setTexture(bg_);
}
