#ifndef SHINY_SPORK_ENTITY_HPP
#define SHINY_SPORK_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Widget.h"
#include "utility/Point.h"

class Entity : public Widget {
 public:
  Entity(State& state, const DrawPriority& priority);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void Click(int, int) override;

  void MouseIn(int, int) override;

  void MouseOut(int, int) override;

  bool PointCheck(int, int) const override;

  void LoadSprite(const std::string& file_name);
  //Устанавливает флаг отображения информации
  virtual void SetInfo(bool value);

 protected:
  sf::Sprite sprite_;
  sf::Sprite icon_sprite_;
  sf::Color default_sprite_color_;
  // Флаг, указывающий находится ли указатель над башней
  bool is_mouse_in_;
  bool is_info_;
};

#endif //SHINY_SPORK_ENTITY_HPP
