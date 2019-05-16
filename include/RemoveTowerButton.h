#ifndef SHINY_SPORK_REMOVETOWERBUTTON_H
#define SHINY_SPORK_REMOVETOWERBUTTON_H

#include <memory>
#include "Button.h"
#include "entity/Tower.h"

class RemoveTowerButton : public Button {
 public:
  explicit RemoveTowerButton(State&, int, int, std::shared_ptr<Tower>);

  void Click(int, int) override;

  void ChangeTower(const std::shared_ptr<Tower>& new_tower) {
    tower_ = new_tower;
  }

 private:
  std::shared_ptr<Tower> tower_;
};

#endif //SHINY_SPORK_REMOVETOWERBUTTON_H
