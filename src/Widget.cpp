#include "Widget.hpp"

Widget::Widget(State& state, const DrawPriority& priority) :
    state_(state),
    priority_(priority) {}

const DrawPriority& Widget::GetPriority() const {
  return priority_;
}


Widget::~Widget() {}
