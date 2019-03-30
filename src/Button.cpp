#include <iostream>
#include "Button.hpp"

Button::Button(State& state, int x, int y, const sf::String& caption) :
    Widget(state, DrawPriority(3,this)),
    bg_sprite_tex_(),
    bg_sprite_(),
    font_(),
    text_() {

  //  TODO(tsmx): absolute crap, replace with proper resource manager ASAP
  sf::Image tex_l, tex_m, tex_r;

  tex_l.loadFromFile("assets/ui/btn_l.png");
  tex_m.loadFromFile("assets/ui/btn_m.png");
  tex_r.loadFromFile("assets/ui/btn_r.png");
  font_.loadFromFile("assets/font/default.ttf");

  text_.setFont(font_);
  text_.setString(caption);
  text_.setOutlineColor(sf::Color::White);
  text_.setCharacterSize(22);
  sf::FloatRect text_bounds = text_.getLocalBounds();
  text_bounds.width+=24;
  sf::Vector2u btn_tile = tex_m.getSize();
  int tile_count = (text_bounds.width + btn_tile.x - 1) / btn_tile.x;

  bg_sprite_tex_.create(tile_count * btn_tile.x, btn_tile.y);
  for (int i = 1; i < tile_count - 1; i++) {
    bg_sprite_tex_.update(tex_m, i * btn_tile.x, 0);
  }
  bg_sprite_tex_.update(tex_l, 0, 0);
  bg_sprite_tex_.update(tex_r, (tile_count - 1) * btn_tile.x, 0);
  bg_sprite_.setTexture(bg_sprite_tex_);

  bg_sprite_.move(x, y);
  text_.setOrigin((text_bounds.width-24 - tile_count * btn_tile.x) / 2,
                  (text_bounds.height - btn_tile.y) / 2 + 5);
  text_.move(x, y);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
  target.draw(text_, states);
}

void Button::Click() {
  std::cerr << "Button clicked\n";
}

void Button::MouseIn() {
  bg_sprite_.setColor(clicked_? sf::Color(255,0,255):sf::Color(200,200,255));
}

void Button::MouseOut() {
  bg_sprite_.setColor(sf::Color::White);
}

bool Button::PointCheck(int x, int y) const {
  return bg_sprite_.getGlobalBounds().contains(x, y);
}
