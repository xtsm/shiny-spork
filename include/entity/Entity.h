#ifndef SHINY_SPORK_ENTITY_HPP
#define SHINY_SPORK_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "Widget.h"
#include "utility/Point.h"

class Entity : public Widget {
 public:
  Entity(State& state, const DrawPriority& priority);
  Entity(State& state, const DrawPriority& priority, int health, int max_health);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  virtual void DecreaseHealth(int delta);

  void Click(int, int) override;

  void MouseIn(int, int) override;

  void MouseOut(int, int) override;

  bool PointCheck(int, int) const override;

  virtual void LoadSprite(const std::string& file_name);
  //Устанавливает флаг отображения информации
  virtual void SetInfo(bool value);

  virtual sf::Sprite GetIconSprite() const;

  virtual std::vector<sf::Text> GetInfo() const;

  void InitText(sf::Text&, int, int, int character_size = 12,
                sf::Color color = sf::Color::White) const;

  double GetCenterX() const;

  double GetCenterY() const;

  void SetSpriteCenter(double, double);

 protected:
  int max_health_;
  int health_;
  sf::RectangleShape health_bar_;
  sf::RectangleShape damage_bar_;
  sf::Sprite sprite_;
  sf::Sprite icon_sprite_;
  sf::Color default_sprite_color_;
  // Флаг, указывающий находится ли указатель над башней
  bool is_mouse_in_;
  bool is_info_;
};

#endif //SHINY_SPORK_ENTITY_HPP
