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

void State::CleanMouseFlags() {
  if (clicked_ != nullptr) {
    clicked_->SetClicked(false);
    clicked_ = nullptr;
  }
  if (hovered_ != nullptr) {
    hovered_->MouseOut();
    hovered_ = nullptr;
  }
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
            if (this == states_.active_state) clicked_->MouseIn();
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
        states_.Close();
        break;

      default:ProcessEvent(event);
    }
  }
}

void State::Close() {
  closed_ = true;
}

ResourceManager<sf::Image> State::images_manager_;
ResourceManager<sf::Font> State::fonts_manager_;
ResourceManager<sf::Texture> State::textures_manager_;

State::~State() {}
StateManager& State::GetStateManager() {
  return states_;
}

ResourceManager<sf::Image>& State::GetImageResourceManager() {
  return images_manager_;
}

ResourceManager<sf::Font>& State::GetFontResourceManager() {
  return fonts_manager_;
}

ResourceManager<sf::Texture>& State::GetTextureResourceManager() {
  return textures_manager_;
}

MockState::MockState(StateManager& manager) : State(manager) {
}
