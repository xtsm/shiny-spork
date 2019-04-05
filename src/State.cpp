#include <iostream>
#include "StateManager.h"
#include "State.h"

State::State(StateManager& states) :
    states_(states),
    render_(),
    draw_queue_(),
    hovered_(nullptr),
    clicked_(nullptr),
    closed_(false) {
  render_.create(800, 600);
}

void State::Render() {
  render_.clear();
  auto it = draw_queue_.end();
  while (it != draw_queue_.begin()) {
    it--;
    render_.draw(**it);
  }
  render_.display();
}

void State::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::Sprite tmp(render_.getTexture());
  target.draw(tmp, states);
}

void State::ProcessEvents(sf::Window& window) {
  sf::Event event{};
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseButtonPressed: {
        if (clicked_ != nullptr) {
          throw std::logic_error("pressed_ isn't nullptr on mouse press event, "
                                 "do you have two mouses or something?");
        }
        for (const std::shared_ptr<Widget>& widget : draw_queue_) {
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
        std::shared_ptr<Widget> new_hovered = nullptr;
        for (const std::shared_ptr<Widget>& widget : draw_queue_) {
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
        states_.Close();
        break;

      default:ProcessEvent(event);
    }
  }
}

void State::Close() {
  closed_ = true;
}

State::~State() = default;

StateManager& State::GetStateManager() {
  return states_;
}

MockState::MockState(StateManager& manager) : State(manager) {
}
