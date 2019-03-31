#ifndef INCLUDE_DRAWPRIORITY_H_
#define INCLUDE_DRAWPRIORITY_H_

class DrawPriority {
 public:
  DrawPriority(int, void*);
  bool operator<(const DrawPriority&) const;
 private:
  int priority_;
  void* obj_ptr_;
};

#endif  // INCLUDE_DRAWPRIORITY_H_
