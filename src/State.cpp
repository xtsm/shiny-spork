#include <State.hpp>

State::State(StateManager& states) :
    states_(states),
    draw_queue_(),
    selected_(nullptr),
    clicked_(nullptr) {}

void State::ProcessEvents(sf::Window& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {

      case sf::Event::MouseButtonPressed:
      case sf::Event::MouseButtonReleased:
      case sf::Event::MouseMoved:
      case sf::Event::MouseEntered:
      case sf::Event::MouseLeft:
        for (Widget* widget : draw_queue_) {
          if (widget->PointCheck(event.mouseButton.x, event.mouseButton.y)) {
            widget->ProcessEvent(event);
            break;
          }
        }
        break;

      case sf::Event::Closed:
        window.close();
        break;

      default:ProcessEvent(event);
    }
  }
}

State::~State() {}
