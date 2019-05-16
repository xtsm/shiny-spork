#include "Widget.h"

int64_t Widget::last_id_ = 0;

Widget::Widget(State& state, const DrawPriority& priority) :
    state_(state),
    priority_(priority),
    clicked_(false),
    x_(0),
    y_(0),
    id_(++last_id_) {}

const DrawPriority& Widget::GetPriority() const {
  return priority_;
}

void Widget::SetClicked(bool clicked) {
  clicked_ = clicked;
}

void Widget::SetPosition(int x, int y) {
  x_ = x;
  y_ = y;
}

int64_t Widget::GetID() const {
  return id_;
}

int Widget::GetX() const {
  return x_;
}

int Widget::GetY() const {
  return y_;
}

void Widget::ChangePriority(DrawPriority priority) {
  priority_ = priority;
}

void Widget::SetLastID(int64_t new_last_id) {
  last_id_ = std::max(last_id_, new_last_id);
}

int64_t Widget::GetLastID() const {
  return last_id_;
}

Widget::~Widget() = default;

