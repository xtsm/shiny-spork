#ifndef INCLUDE_PAUSESTATE_H_
#define INCLUDE_PAUSESTATE_H_
#include "State.h"
#include "Background.h"

class PauseState : public State {
 public:
  explicit PauseState(StateManager& states);
  void Tick();
  void UpdateBackground(const sf::Texture& texture);
  void ProcessEvent(sf::Event& event);
 protected:
  Background background_;
};

#endif  // INCLUDE_PAUSESTATE_H_
