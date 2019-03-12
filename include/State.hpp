#pragma once
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <set>

class StateManager;

class State : public sf::Drawable {
 public:
  State(StateManager& states);
  virtual void Tick() = 0;
  void draw(sf::RenderTarget&, sf::RenderStates) const;

  //  Для обработки глобальных событий (т.е. не привязанных к курсору мыши)
  virtual void ProcessEvent(sf::Event& ) = 0;

  //  Для обработки вообще всех событий, вызывается из main
  void ProcessEvents(sf::Window& window);

 protected:
//  Компаратор для очереди рисования
  struct QueueCmp {
    bool operator()(Widget* lhs, Widget* rhs) const {
      return lhs->GetPriority() < rhs->GetPriority();
    }
  };

//  Непосредственно Widget-ы, отсортированные по приоритету
  StateManager& states_;
  std::set<Widget*, State::QueueCmp> draw_queue_;
  Widget* hovered_;
  Widget* clicked_;

  virtual ~State();

 private:
  State(const State&) = delete;
  State& operator=(const State&) = delete;
};

class MockState : public State {
 public:
  MockState(StateManager&);
  void Tick() final {}
  void ProcessEvent(sf::Event& ) final {}
};
