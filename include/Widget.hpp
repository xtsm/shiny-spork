#pragma once
#include <SFML/Graphics.hpp>

class State;

class Widget {
 public:
//  Принимает state, кооторому принадлежит Widget
  explicit Widget(State& state);

//  Обрабатывает события
  virtual void ProcessEvent(sf::Event& event) = 0;

//  Проверяет приналдежность точки виджету
  virtual const bool PointCheck(int x, int y) = 0;

 protected:
  State& state;
};