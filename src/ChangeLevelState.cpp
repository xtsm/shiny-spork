#include <SFML/Graphics.hpp>
#include "State.h"
#include "ChangeLevelState.h"

void ChangeLevelState::Tick() {}

void ChangeLevelState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  State::draw(target, states);
}

