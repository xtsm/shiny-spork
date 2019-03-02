#include <State.hpp>

State::State(StateManager& states) : states(states) {}

void State::ProcessEvents(sf::Window& window) {
  sf::Event event{};

  while (window.pollEvent(event)) {

    switch (event.type) {

      case sf::Event::MouseButtonPressed:
        for (const auto priority_widget : WidgetPriorityQueue) {
          if (priority_widget.widget.PointCheck(event.mouseButton.x,
                                                event.mouseButton.y)) {
            priority_widget.widget.ProcessEvent(event);
            break;
          }
        }
        break;

      default:ProcessEvent(event);
    }
  }
}
