#include "Widget.hpp"

Widget::Widget(State& state, const DrawPriority& priority) :
    state_(state),
    priority_(priority),
    clicked_(false) {}

const DrawPriority& Widget::GetPriority() const {
  return priority_;
}

void Widget::SetClicked(bool clicked) {
  clicked_ = clicked;
}

Widget::~Widget() {}
