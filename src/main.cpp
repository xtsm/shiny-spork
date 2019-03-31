#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "ExitButton.h"

int main() {
  sf::RenderWindow wnd(sf::VideoMode(800, 600), "", sf::Style::Titlebar);
  wnd.setVerticalSyncEnabled(true);
  wnd.setPosition(sf::Vector2i(400, 300));
  StateManager states;
  while (!states.Closed()) {
    wnd.clear();
    states.GetActiveState()->ProcessEvents(wnd);
    states.GetActiveState()->Tick();
    wnd.draw(*states.GetActiveState());
    wnd.display();
  }
  wnd.close();
  return 0;
}
