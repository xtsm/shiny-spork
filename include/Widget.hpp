#pragma once
#include <SFML/Graphics.hpp>
#include "DrawPriority.hpp"

class State;

class Widget : public sf::Drawable {
 public:
  //  Принимает state, кооторому принадлежит Widget
  explicit Widget(State& state, const DrawPriority&);

  //  Проверяет приналдежность точки виджету
  virtual bool PointCheck(int, int) const { return false; };

  virtual void Click() {}
  virtual void MouseIn() {}
  virtual void MouseOut() {}

  void SetClicked(bool);
  virtual void SetPosition(int x,int y);

  //  Получает проиоритет в очереди рисования и обработки событий
  const DrawPriority& GetPriority() const;
 protected:
  ~Widget() override;
  State& state_;
  DrawPriority priority_;
  bool clicked_;
  int x_, y_;
};
