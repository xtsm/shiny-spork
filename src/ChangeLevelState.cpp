#include <SFML/Graphics.hpp>
#include "State.h"
#include "ChangeLevelState.h"
#include "ChangeLevelButton.h"
#include "Background.h"

void ChangeLevelState::Tick() {}

void ChangeLevelState::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  State::draw(target, states);
}

ChangeLevelState::ChangeLevelState(StateManager& manager) :
    State(manager),
    change_level_(new ChangeLevelButton(*this)),
    background_(new Background(*this, 3)),
    menu_(new MainMenuButton(*this, 500, 500)) {
  background_->SetDim(true);
  draw_queue_.insert(background_);
  draw_queue_.insert(change_level_);
  draw_queue_.insert(menu_);
}

void ChangeLevelState::ProcessEvent(sf::Event&) {}

void ChangeLevelState::ChangeBackground(const sf::Texture& texture) {
  background_->LoadFromTexture(texture);
}
