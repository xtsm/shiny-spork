#pragma once
#include <SFML/Graphics.hpp>
#include "DrawPriority.hpp"

class State;

class Widget : public sf::Drawable {
 public:
  //  Принимает state, кооторому принадлежит Widget
  explicit Widget(State& state, const DrawPriority&);

  //  Проверяет приналдежность точки виджету
  virtual bool PointCheck(int x, int y) const = 0;

  virtual void Click() = 0;
  virtual void MouseIn() = 0;
  virtual void MouseOut() = 0;

  void SetClicked(bool);

  //  Получает проиоритет в очереди рисования и обработки событий
  const DrawPriority& GetPriority() const;
 protected:
  virtual ~Widget();
  State& state_;
  DrawPriority priority_;
  bool clicked_;
};
