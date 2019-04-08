#ifndef INCLUDE_WIDGET_H_
#define INCLUDE_WIDGET_H_
#include <SFML/Graphics.hpp>
#include "DrawPriority.h"
#include "utility/ResourceManager.h"

class State;

class Widget : public sf::Drawable {
 public:
  //  Принимает state, которому принадлежит Widget
  explicit Widget(State& state, const DrawPriority&);

  //  Проверяет приналдежность точки виджету
  virtual bool PointCheck(int, int) const { return false; }

  virtual void Click() {}
  virtual void MouseIn() {}
  virtual void MouseOut() {}

  void SetClicked(bool);
  virtual void SetPosition(int x, int y);

  long long GetID() const;

  //  Получает проиоритет в очереди рисования и обработки событий
  const DrawPriority& GetPriority() const;
 protected:
  ~Widget() override;
  State& state_;
  DrawPriority priority_;
  bool clicked_;
  int x_, y_;
  long long id_;
  static long long last_id_;
};

#endif  // INCLUDE_WIDGET_H_
