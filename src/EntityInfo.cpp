#include "EntityInfo.h"

EntityInfo::EntityInfo(State& state, const sf::Sprite& image,
                       const std::vector<sf::Text>& info)
    : Widget(state, DrawPriority(1000, this)),
      image_of_entity_(image),
      some_info_about_entity_(info.begin(), info.end()),
      amount_of_lines_(static_cast<int>(info.size())),
      max_amount_of_lines_(6) {
  if (static_cast<int>(info.size()) > max_amount_of_lines_) {
    throw std::invalid_argument("Sorry, but we accept less or equal 6 lines of info");
  }
}

void EntityInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(image_of_entity_, states);
  for (const auto& text : some_info_about_entity_) {
    target.draw(text, states);
  }
}
