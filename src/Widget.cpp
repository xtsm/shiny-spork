#include "Widget.h"

Widget::Widget(State& state, const DrawPriority& priority) :
    state_(state),
    priority_(priority),
    clicked_(false),
    x_(0),
    y_(0) {}

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

Widget::~Widget() {}
