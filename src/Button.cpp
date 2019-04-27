#include <iostream>
#include "Button.h"
#include "State.h"

Button::Button(State& state, int priority, int x, int y, const std::string& caption) :
    Widget(state, DrawPriority(priority, this)),
    bg_sprite_tex_(),
    bg_sprite_(),
    font_(),
    text_(),
    disable_(false) {
  // TODO(tsmx): absolute crap, replace with proper resource manager ASAP
  bg_sprite_.setPosition(x, y);
  text_.setPosition(x, y);
  font_ = State::GetFontResourceManager()
      .GetOrLoadResource("assets/font/default.ttf");
  text_.setFont(font_);
  text_.setOutlineColor(sf::Color::White);
  text_.setCharacterSize(22);
  ChangeText(caption);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
  target.draw(text_, states);
}

void Button::ChangeText(const std::string& caption) {
  sf::Image& tex_l = State::GetImageResourceManager()
      .GetOrLoadResource("assets/ui/btn_l.png");
  sf::Image& tex_m = State::GetImageResourceManager()
      .GetOrLoadResource("assets/ui/btn_m.png");
  sf::Image& tex_r = State::GetImageResourceManager()
      .GetOrLoadResource("assets/ui/btn_r.png");

  text_.setString(caption);
  sf::FloatRect text_bounds = text_.getLocalBounds();
  text_bounds.width += 24;
  sf::Vector2u btn_tile = tex_m.getSize();
  int tile_count = static_cast<int>(text_bounds.width + btn_tile.x - 1);
  tile_count /= btn_tile.x;

  bg_sprite_.setTextureRect(sf::IntRect(0, 0, tile_count * btn_tile.x, btn_tile.y));
  bg_sprite_tex_.create(tile_count * btn_tile.x, btn_tile.y);
  for (int i = 1; i < tile_count - 1; i++) {
    bg_sprite_tex_.update(tex_m, i * btn_tile.x, 0);
  }
  bg_sprite_tex_.update(tex_l, 0, 0);
  bg_sprite_tex_.update(tex_r, (tile_count - 1) * btn_tile.x, 0);
  bg_sprite_.setTexture(bg_sprite_tex_);

  text_.setOrigin((text_bounds.width - 24 - tile_count * btn_tile.x) / 2,
                  (text_bounds.height - btn_tile.y) / 2 + 5);
}

void Button::Click(int, int) {
  std::cerr << "Button clicked\n";
}

void Button::MouseIn(int, int) {
  if (disable_ && clicked_) {
    bg_sprite_.setColor(sf::Color(255, 0, 0));
  } else if (disable_) {
    bg_sprite_.setColor(sf::Color(40, 40, 40));
  } else if (clicked_) {
    bg_sprite_.setColor(sf::Color(255, 0, 255));
  } else {
    bg_sprite_.setColor(sf::Color(200, 200, 255));
  }
}

void Button::MouseOut(int, int) {
  if (disable_) {
    bg_sprite_.setColor(sf::Color(80, 80, 80));
  } else {
    bg_sprite_.setColor(sf::Color::White);
  }
}

bool Button::PointCheck(int x, int y) const {
  return bg_sprite_.getGlobalBounds().contains(x, y);
}

void Button::SetDisable(bool value) {
  disable_ = value;
  if (disable_) {
    bg_sprite_.setColor(sf::Color(80, 80, 80));
  } else {
    bg_sprite_.setColor(sf::Color::White);
  }
}
