#ifndef INCLUDE_PAUSESTATE_H_
#define INCLUDE_PAUSESTATE_H_
#include "State.h"
#include "Background.h"

class PauseState : public State {
 public:
  explicit PauseState(StateManager& states);
  void Tick() override;
  void UpdateBackground(const sf::Texture& texture);
  void ProcessEvent(sf::Event& event) override;
 protected:
  std::shared_ptr<Background> background_ptr_;
};

#endif  // INCLUDE_PAUSESTATE_H_
