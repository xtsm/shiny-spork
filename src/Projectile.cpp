#include "Projectile.h"

Projectile::Projectile(State& state, const DrawPriority& priority, int x, int y) :
    Widget(state, priority),
    sprite_tex_(),
    sprite_(),
    damage_(0) {
  SetPosition(x, y);
  //TODO
}
void Projectile::draw(sf::RenderTarget&, sf::RenderStates) const {
  //TODO
}


