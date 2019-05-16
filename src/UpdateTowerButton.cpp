#include "UpdateTowerButton.h"
#include "StateManager.h"
#include "GameState.h"

UpdateTowerButton::UpdateTowerButton(State& state, int x, int y, std::shared_ptr<Tower> tower) :
    Button(state, 1005, x, y, "Update"),
    tower_(std::move(tower)),
    coins_sprite_(),
    is_view_coins_sprite_(false) {
  coins_sprite_.setTexture(State::GetTextureResourceManager().
      GetOrLoadResource("assets/ui/coins.png"));
  double max_side = std::max(
      coins_sprite_.getGlobalBounds().height, coins_sprite_.getGlobalBounds().width);
  coins_sprite_.setScale(22 / max_side, 22 / max_side);
  coins_sprite_.setPosition(x + 100, y + 15);
}

void UpdateTowerButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(bg_sprite_, states);
  target.draw(text_);
  if (is_view_coins_sprite_) {
    target.draw(coins_sprite_);
  }
}

void UpdateTowerButton::Click(int, int) {
  if (!disable_) {
    tower_->Update();
    state_.GetStateManager().game_ptr_->
        ChangeBalance(-tower_->GetUpdateCost());
    if (!tower_->Updatable()) {
      SetDisable(true);
    }
    UpdateCaption();
  }
}

void UpdateTowerButton::ChangeTower(const std::shared_ptr<Tower>& new_tower) {
  tower_ = new_tower;
  if (tower_ != nullptr) {
    UpdateCaption();
    SetDisable(!tower_->Updatable());
  }
}

void UpdateTowerButton::CheckAvailability(int balance_) {
  SetDisable(tower_ == nullptr || !tower_->Updatable() || tower_->GetUpdateCost() > balance_);
}

void UpdateTowerButton::SetDisable(bool value) {
  Button::SetDisable(value);
  if (disable_) {
    coins_sprite_.setColor(sf::Color(80, 80, 80));
    text_.setFillColor(sf::Color(80, 80, 80));
  } else {
    coins_sprite_.setColor(sf::Color::White);
    text_.setFillColor(sf::Color::White);
  }
}

void UpdateTowerButton::UpdateCaption() {
  if (tower_ == nullptr || !tower_->Updatable()) {
    is_view_coins_sprite_ = false;
    ChangeText("Update");
  } else {
    is_view_coins_sprite_ = true;
    ChangeText("Update:   " + std::to_string(tower_->GetUpdateCost()));
  }
}
