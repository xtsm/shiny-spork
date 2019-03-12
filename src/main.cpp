#include <SFML/Graphics.hpp>
#include <StateManager.hpp>
#include "ExitButton.hpp"

int main() {
  sf::RenderWindow wnd(sf::VideoMode(800,600),"",
      sf::Style::Titlebar);
  wnd.setVerticalSyncEnabled(true);
  StateManager states;
  MockState state(states);
  ExitButton exit(state, 0, 0, "Exit", wnd);
  while (wnd.isOpen()) {
    wnd.clear();
    wnd.draw(exit);
    states.GetActiveState()->ProcessEvents(wnd);
    states.GetActiveState()->Tick();
    wnd.draw(*states.GetActiveState());
    wnd.display();
  }
  return 0;
}
