#include <fstream>
#include "SettingsState.h"
#include "Button.h"
#include "StateManager.h"

SettingsState::SettingsState(StateManager& states) :
    State(states),
    width_(0),
    height_(0),
    main_menu_button_ptr_(new MainMenuButton(*this, 50, 350)),
    background_ptr_(new Background(*this, 5)) {
  draw_queue_.insert(main_menu_button_ptr_);
  background_ptr_->LoadFromFile("assets/ui/main_menu.png");
  background_ptr_->SetSize(800, 600);
  draw_queue_.insert(background_ptr_);
}

void SettingsState::Tick() {
  if (closed_) {
    states_.Close();
    closed_ = false;
  }
}
void SettingsState::ProcessEvent(sf::Event&) {
}
