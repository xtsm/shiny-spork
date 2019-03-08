#pragma once

class DrawPriority {
public:
  DrawPriority(int);
  bool operator<(const DrawPriority&) const;
private:
  int priority_;
};
