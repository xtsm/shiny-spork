#pragma once
#include <SFML/Graphics.hpp>
#include <Widget.hpp>
#include <set>

class StateManager;

class State {
 public:
  State(StateManager& states);
  virtual void Tick() = 0;
  virtual void Draw(sf::RenderTarget& target) = 0;
  virtual void ProcessEvent(sf::Event& event) = 0;
  void ProcessEvents(sf::Window& window);
  //  Структурка для сотировки Widget по приоритету
  struct PriorityWidget {
   public:
    PriorityWidget(Widget& widget, int priority) : widget(widget), priority_(priority) {}
    friend bool operator<(State::PriorityWidget lhs, State::PriorityWidget rhs) {
      return lhs.priority_ < rhs.priority_;
    }
    Widget& widget;
   private:
    int priority_;
  };

 protected:
//  Непосредственно Widgetы, отсортированные по приоритету
  std::set<PriorityWidget> WidgetPriorityQueue;
  StateManager& states;
};



