#pragma once
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <set>

class StateManager;

class State {
 public:
  State(StateManager& states);
  virtual void Tick() = 0;
  virtual void Draw(sf::RenderTarget&) = 0;

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
  Widget* selected_;
  Widget* clicked_;

  virtual ~State();

 private:
  State(const State&) = delete;
  State& operator=(const State&) = delete;
};



