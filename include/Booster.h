#ifndef SHINY_SPORK_BOOSTER_H
#define SHINY_SPORK_BOOSTER_H

#include "State.h"

class Booster {
 public:
  Booster(State& state, int cooldown);

  void Save(std::ofstream& fout);

  void AddBooster(int boost, int64_t time);

  int Boost();

  int GetMin() const;

  int GetMax() const;

  int GetCooldown() const;

 protected:
  State& state_;
  std::map<int, int64_t> boosters_;
  int timer_;
  bool boosted_;
  const int cooldown_;
};

#endif //SHINY_SPORK_BOOSTER_H
