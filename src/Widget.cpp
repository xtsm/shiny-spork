#include "Widget.h"

long long Widget::last_id_ = 0;

Widget::Widget(State& state, const DrawPriority& priority) :
    state_(state),
    priority_(priority),
    clicked_(false),
    x_(0),
    y_(0),
    id_(last_id_++) {}

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

Widget::~Widget() = default;
