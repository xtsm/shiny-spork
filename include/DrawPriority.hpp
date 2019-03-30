#pragma once

class DrawPriority {
public:
  DrawPriority(int, void*);
  bool operator<(const DrawPriority&) const;
private:
  int priority_;
  void* obj_ptr_;
};
