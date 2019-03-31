#ifndef SHINY_SPORK_BACKGOUND_HPP
#define SHINY_SPORK_BACKGOUND_HPP
#include <Widget.hpp>
#include <State.hpp>
#include <string>

class Background : public Widget {
 public:
  explicit Background(State& state);

  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

  void LoadFromFile(const std::string& file_name);

  void SetSize(int w, int h);

  void SetPosition(int x,int y) override;

 private:
  sf::Texture bg_;
  sf::Sprite bg_sprite_;
};

#endif //SHINY_SPORK_BACKGOUND_HPP
