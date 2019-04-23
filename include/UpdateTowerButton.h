#ifndef INCLUDE_UPDATETOWERBUTTON_H_
#define INCLUDE_UPDATETOWERBUTTON_H_

#include <memory>
#include "Button.h"
#include "entity/Tower.h"

class UpdateTowerButton : public Button {
 public:
  explicit UpdateTowerButton(State&, int, int, std::shared_ptr<Tower>);

  void Click(int, int) override;

  void ChangeTower(const std::shared_ptr<Tower>&);

 private:
  std::shared_ptr<Tower> tower_;
};

#endif  // INCLUDE_UPDATETOWERBUTTON_H_
