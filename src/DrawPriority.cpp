#include "DrawPriority.hpp"

DrawPriority::DrawPriority(int priority) :
    priority_(priority) {
}
bool DrawPriority::operator<(const DrawPriority& oth) const {
  return priority_ < oth.priority_;
}

