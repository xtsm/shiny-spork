#include "Projectile.h"

Projectile::Projectile(State& state, const DrawPriority& priority,
    int x, int y) :
    Widget(state, priority),
    sprite_tex_(),
    sprite_(),
    damage_(0) {
  SetPosition(x, y);
  // TODO(Nicksechko): Цель
}
void Projectile::draw(sf::RenderTarget&, sf::RenderStates) const {
  // TODO(Nicksechko): Полёт
}


