#include "DrawPriority.h"
#include <tuple>

DrawPriority::DrawPriority(int priority, void* obj_ptr) :
    priority_(priority), obj_ptr_(obj_ptr) {
}
bool DrawPriority::operator<(const DrawPriority& oth) const {
  return std::tie(priority_,obj_ptr_) < std::tie(oth.priority_,oth.obj_ptr_);
}

