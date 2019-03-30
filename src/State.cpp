#include <iostream>
#include <State.hpp>

#include "State.hpp"

State::State(StateManager& states) :
    states_(states),
    draw_queue_(),
    hovered_(nullptr),
    clicked_(nullptr),
    closed_(false) {
}


void State::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  for (Widget* widget : draw_queue_) {
    target.draw(*widget, states);
  }
}

void State::ProcessEvents(sf::Window& window) {
  sf::Event event;
  while (window.pollEvent(event)) {
    switch (event.type) {

      case sf::Event::MouseButtonPressed: {
        if (clicked_ != nullptr) {
          throw std::logic_error("pressed_ isn't nullptr on mouse press event, "
                                 "do you have two mouses or something?");
        }
        for (Widget* widget : draw_queue_) {
          if (widget->PointCheck(event.mouseButton.x, event.mouseButton.y)) {
            clicked_ = widget;
            clicked_->SetClicked(true);
            clicked_->MouseIn();
            break;
          }
        }
        break;
      }
      case sf::Event::MouseButtonReleased: {
        if (clicked_ != nullptr) {
          clicked_->SetClicked(false);
          if (clicked_->PointCheck(event.mouseButton.x, event.mouseButton.y)) {
            clicked_->Click();
            clicked_->MouseIn();
          }
          clicked_ = nullptr;
        }
        break;
      }

      case sf::Event::MouseMoved: {
        if (hovered_ != nullptr &&
            hovered_->PointCheck(event.mouseMove.x, event.mouseMove.y)) {
          break;
        }
        Widget* new_hovered = nullptr;
        for (Widget* widget : draw_queue_) {
          if (widget->PointCheck(event.mouseMove.x, event.mouseMove.y)) {
            new_hovered = widget;
            break;
          }
        }
        if (hovered_ != nullptr) hovered_->MouseOut();
        hovered_ = new_hovered;
        if (hovered_ != nullptr) hovered_->MouseIn();
        break;
      }

      case sf::Event::MouseLeft:
        if (hovered_ != nullptr) hovered_->MouseOut();
        hovered_ = nullptr;
        break;

      case sf::Event::Closed:
        window.close();
        break;

      default:ProcessEvent(event);
    }
  }
}

void State::Close() {
  closed_ = true;
}

State::~State() {}

MockState::MockState(StateManager& manager) : State(manager) {

}
