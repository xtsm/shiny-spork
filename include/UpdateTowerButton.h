#ifndef INCLUDE_UPDATETOWERBUTTON_H_
#define INCLUDE_UPDATETOWERBUTTON_H_

#include <memory>
#include "Button.h"
#include "entity/Tower.h"

class UpdateTowerButton : public Button {
 public:
  explicit UpdateTowerButton(State&, int, int, std::shared_ptr<Tower>);

  void draw(sf::RenderTarget&, sf::RenderStates) const override;

  void Click(int, int) override;

  void ChangeTower(const std::shared_ptr<Tower>&);

  void CheckAvailability(int balance_);

  void SetDisable(bool value) override;

  void UpdateCaption();

 private:
  std::shared_ptr<Tower> tower_;
  sf::Sprite coins_sprite_;
  bool is_view_coins_sprite_;
};

#endif  // INCLUDE_UPDATETOWERBUTTON_H_
