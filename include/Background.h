#ifndef INCLUDE_BACKGROUND_H_
#define INCLUDE_BACKGROUND_H_
#include <string>
#include "Widget.h"
#include "State.h"

class Background : public Widget {
 public:
  explicit Background(State& state, int priority);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void Click(int, int) override;

  bool PointCheck(int, int) const override;

  void LoadFromFile(const std::string& file_name);

  void LoadFromTexture(const sf::Texture& texture);

  void SetSize(int w, int h);

  void SetDim(bool value);

  void SetPosition(int x, int y) override;

 private:
  sf::Sprite bg_sprite_;
};

#endif  // INCLUDE_BACKGROUND_H_
