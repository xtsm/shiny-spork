#ifndef SHINY_SPORK_REMOVETOWERBUTTON_H
#define SHINY_SPORK_REMOVETOWERBUTTON_H

#include <memory>
#include "Button.h"
#include "Tower.h"

class RemoveTowerButton : public Button {
 public:
  explicit RemoveTowerButton(State&, int, int, std::shared_ptr<Tower>);

  void Click(int, int) override;

 private:
  std::shared_ptr<Tower> tower_;
};

#endif //SHINY_SPORK_REMOVETOWERBUTTON_H
