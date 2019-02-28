#include <MainMenuState.hpp>

MainMenuState::MainMenuState(StateManager& states) : State(states) {
}
void MainMenuState::Tick() {
}
void MainMenuState::Draw(sf::RenderTarget &target) {
}
void MainMenuState::ProcessEvents(sf::Window &wnd) {
  sf::Event evt;
  while (wnd.pollEvent(evt)) {
    if (evt.type == sf::Event::Closed) wnd.close();
  }
}
