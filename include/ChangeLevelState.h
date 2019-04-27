#ifndef SHINY_SPORK_CHANGELEVELSTATE_H
#define SHINY_SPORK_CHANGELEVELSTATE_H

#include <memory>
#include "State.h"
#include "StateManager.h"
#include "ChangeLevelButton.h"
#include "MainMenuButton.h"

class ChangeLevelState : public State {
 public:
  ChangeLevelState(StateManager& manager);

  void Tick() override;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
  void ProcessEvent(sf::Event& event) override;

 private:
  std::shared_ptr<ChangeLevelButton> change_level_;
  std::shared_ptr<MainMenuButton> menu_;
};

#endif //SHINY_SPORK_CHANGELEVELSTATE_H
