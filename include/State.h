#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>
#include "Widget.h"
#include "utility/ResourceManager.h"

class StateManager;

class State : public sf::Drawable {
 public:
  explicit State(StateManager& states);
  virtual void Tick() = 0;
  void draw(sf::RenderTarget&, sf::RenderStates) const override;

  //  Для обработки глобальных событий (т.е. не привязанных к курсору мыши)
  virtual void ProcessEvent(sf::Event& event) = 0;

  void Render();

  //  Для обработки вообще всех событий, вызывается из main
  void ProcessEvents(sf::RenderWindow& window);

  StateManager& GetStateManager();

  void Close();

  State(const State&) = delete;

  State& operator=(const State&) = delete;

  // Очистка clicked_ и hovered_ при переходе между стейтами
  void CleanMouseFlags();

  static ResourceManager<sf::Image>& GetImageResourceManager();

  static ResourceManager<sf::Font>& GetFontResourceManager();

  static ResourceManager<sf::Texture>& GetTextureResourceManager();

 protected:
//  Компаратор для очереди рисования
  struct QueueCmp {
    bool operator()(const std::shared_ptr<Widget>& lhs,
        const std::shared_ptr<Widget>& rhs) const {
      return lhs->GetPriority() > rhs->GetPriority();
    }
  };

//  Непосредственно Widget-ы, отсортированные по приоритету
  StateManager& states_;
  sf::RenderTexture render_;
  std::set<std::shared_ptr<Widget>, State::QueueCmp> draw_queue_;
  std::shared_ptr<Widget> hovered_;
  std::shared_ptr<Widget> clicked_;
  bool closed_;

  ~State() override;

 private:
  static ResourceManager<sf::Texture> textures_manager_;
  static ResourceManager<sf::Font> fonts_manager_;
  static ResourceManager<sf::Image> images_manager_;
};

class MockState : public State {
 public:
  explicit MockState(StateManager&);
  void Tick() final {}
  void ProcessEvent(sf::Event&) final {}
};

#endif  // INCLUDE_STATE_H_
