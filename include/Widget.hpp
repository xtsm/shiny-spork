#pragma once
#include <SFML/Graphics.hpp>
#include "DrawPriority.hpp"

class State;

class Widget {
 public:
  //  Принимает state, кооторому принадлежит Widget
  explicit Widget(State& state, const DrawPriority&);

  //  Обрабатывает события
  virtual void ProcessEvent(sf::Event& event) = 0;

  //  Проверяет приналдежность точки виджету
  virtual bool PointCheck(int x, int y) const = 0;

  //  Получает проиоритет в очереди рисования и обработки событий
  const DrawPriority& GetPriority() const;
 protected:
  virtual ~Widget();
  State& state_;
  DrawPriority priority_;
};
