#include <SFML/Graphics.hpp>
#include <StateManager.hpp>

int main() {
  sf::RenderWindow wnd(sf::VideoMode(800,600),"",sf::Style::Titlebar);
  wnd.setVerticalSyncEnabled(true);
  StateManager states;

  while (wnd.isOpen()) {
    wnd.clear();
    states.GetActiveState()->ProcessEvents(wnd);
    states.GetActiveState()->Tick();
    states.GetActiveState()->Draw(wnd);
    wnd.display();
  }
  return 0;
}
