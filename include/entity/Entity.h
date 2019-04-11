#ifndef SHINY_SPORK_ENTITY_HPP
#define SHINY_SPORK_ENTITY_HPP

#include <SFML/Graphics.hpp>
#include "Widget.h"

class Entity : public Widget {
 public:
  Entity(State& state, const DrawPriority& priority);

  virtual void SetInfo(bool value);

 protected:
  bool is_info_;
};

#endif //SHINY_SPORK_ENTITY_HPP
