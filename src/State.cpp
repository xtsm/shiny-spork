#include <iostream>

#include "StateManager.h"
#include "State.h"
#include <memory>

State::State(StateManager& states) :
    states_(states),
    render_(),
    draw_queue_(),
    hovered_(nullptr),
    clicked_(nullptr),
    closed_(false) {
  render_.create(800, 600);
}

sf::Vector2u State::ConvertCoordsR2V(sf::Vector2u v, sf::Vector2u sz) {
  double factor = std::min(sz.x / 800.0, sz.y / 600.0);
  return sf::Vector2u(
      (v.x - sz.x / 2.0) / factor + 400,
      (v.y - sz.y / 2.0) / factor + 300);
}

void State::CleanMouseFlags() {
  if (clicked_ != nullptr) {
    clicked_->SetClicked(false);
    clicked_ = nullptr;
  }
  if (hovered_ != nullptr) {
    hovered_->MouseOut(0, 0);
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
  sf::Sprite sprite(render_.getTexture());
  sf::Vector2u size = target.getSize();
  double factor = std::min(size.x / 800.0, size.y / 600.0);
  sprite.setScale(factor, factor);
  sprite.setOrigin(400, 300);
  sprite.setPosition(size.x / 2, size.y / 2);
  target.draw(sprite, states);
}

void State::ProcessEvents(sf::RenderWindow& window) {
  sf::Event event{};
  while (window.pollEvent(event)) {
    switch (event.type) {
      case sf::Event::MouseButtonPressed: {
        if (clicked_ != nullptr) {
          throw std::logic_error("pressed_ isn't nullptr on mouse press event, "
                                 "do you have two mouses or something?");
        }
        for (const std::shared_ptr<Widget>& widget : draw_queue_) {
          sf::Vector2u click_point(event.mouseButton.x, event.mouseButton.y);
          click_point = ConvertCoordsR2V(click_point, window.getSize());
          if (widget->PointCheck(click_point.x, click_point.y)) {
            clicked_ = widget;
            clicked_->SetClicked(true);
            clicked_->MouseIn(click_point.x, click_point.y);
            break;
          }
        }
        break;
      }
      case sf::Event::MouseButtonReleased: {
        if (clicked_ != nullptr) {
          clicked_->SetClicked(false);
          sf::Vector2u click_point(event.mouseButton.x, event.mouseButton.y);
          click_point = ConvertCoordsR2V(click_point, window.getSize());
          if (clicked_->PointCheck(click_point.x, click_point.y)) {
            clicked_->Click(click_point.x, click_point.y);
            if (states_.active_state_ptr_.get() == this) {
              clicked_->MouseIn(click_point.x, click_point.y);
            }
          }
          clicked_ = nullptr;
        }
        break;
      }

      case sf::Event::MouseMoved: {
        sf::Vector2u hover_point(event.mouseMove.x, event.mouseMove.y);
        hover_point = ConvertCoordsR2V(hover_point, window.getSize());
        std::shared_ptr<Widget> new_hovered = nullptr;
        for (const std::shared_ptr<Widget>& widget : draw_queue_) {
          if (widget->PointCheck(hover_point.x, hover_point.y)) {
            new_hovered = widget;
            break;
          }
        }
        if (hovered_ != nullptr) hovered_->MouseOut(hover_point.x, hover_point.y);
        hovered_ = new_hovered;
        if (hovered_ != nullptr) {
          hovered_->MouseIn(hover_point.x, hover_point.y);
          hovered_->MouseMove(hover_point.x, hover_point.y);
        }
        break;
      }

      case sf::Event::MouseLeft:if (hovered_ != nullptr) hovered_->MouseOut(-1, -1);
        hovered_ = nullptr;
        break;

      case sf::Event::Closed:
        states_.Close();
        break;

      case sf::Event::Resized: {
        // не имею понятия, что эта хренотень делает,
        // но ресайз без этого не работает
        int w = event.size.width;
        int h = event.size.height;
        window.setView(sf::View(sf::FloatRect(0, 0, w, h)));
        break;
      }

      default:ProcessEvent(event);
    }
  }
}

void State::Close() {
  closed_ = true;
}

State::~State() = default;

ResourceManager<sf::Image> State::images_manager_;
ResourceManager<sf::Font> State::fonts_manager_;
ResourceManager<sf::Texture> State::textures_manager_;
ResourceManager<sf::SoundBuffer> State::sound_manager_;

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

ResourceManager<sf::SoundBuffer>& State::GetSoundResourceManager() {
  return sound_manager_;
}

MockState::MockState(StateManager& manager) : State(manager) {
}
