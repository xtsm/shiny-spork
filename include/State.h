#ifndef INCLUDE_STATE_H_
#define INCLUDE_STATE_H_
#include <SFML/Graphics.hpp>
#include <set>
#include "Widget.h"

class StateManager;

class State : public sf::Drawable {
 public:
  explicit State(StateManager& states);
  virtual void Tick() = 0;
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  //  Для обработки глобальных событий (т.е. не привязанных к курсору мыши)
  virtual void ProcessEvent(sf::Event& event) = 0;

  void Render();

  //  Для обработки вообще всех событий, вызывается из main
  void ProcessEvents(sf::Window& window);

  StateManager& GetStateManager();

  void Close();

 protected:
//  Компаратор для очереди рисования
  struct QueueCmp {
    bool operator()(Widget* lhs, Widget* rhs) const {
      return lhs->GetPriority() < rhs->GetPriority();
    }
  };

//  Непосредственно Widget-ы, отсортированные по приоритету
  StateManager& states_;
  sf::RenderTexture render_;
  std::set<Widget*, State::QueueCmp> draw_queue_;
  Widget* hovered_;
  Widget* clicked_;
  bool closed_;

  virtual ~State();

 private:
  State(const State&) = delete;
  State& operator=(const State&) = delete;
};

class MockState : public State {
 public:
  explicit MockState(StateManager&);
  void Tick() final {}
  void ProcessEvent(sf::Event&) final {}
};

#endif  // INCLUDE_STATE_H_
