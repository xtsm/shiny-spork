#pragma once
#include <SFML/Graphics.hpp>
#include <set>

class StateManager;
class Widget;

class State {
 public:
  State(StateManager& states);
  virtual void Tick() = 0;
  virtual void Draw(sf::RenderTarget& target) = 0;
  virtual void ProcessEvents(sf::Window& wnd) = 0;
 protected:
//  Структурка для сотировки Widget по приоритету
  struct PriorityWidget {
   public:
    PriorityWidget(int priority, Widget& widget) : priority_(priority), widget_(widget) {}
    friend bool operator<(State::PriorityWidget lhs, State::PriorityWidget rhs) {
      return lhs.priority_ < rhs.priority_;
    }
   private:
    int priority_;
    Widget& widget_;
  };
//  Непосредственно Widgetы, отсортированные по приоритету
  std::set<PriorityWidget> WidgetPriorityQueue;
  StateManager& states;
};



