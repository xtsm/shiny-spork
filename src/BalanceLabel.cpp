#include "BalanceLabel.h"
#include "GameState.h"

BalanceLabel::BalanceLabel(State& state, int x, int y, int balance) :
    Widget(state, DrawPriority(1005, this)),
    balance_(balance),
    text_(),
    coins_sprite_() {
  SetPosition(x, y);
  Init();
}

BalanceLabel::BalanceLabel(State& state, std::istream& in) :
    Widget(state, DrawPriority(1005, this)),
    balance_(0),
    text_(),
    coins_sprite_() {
  in >> x_ >> y_;
  in >> balance_;
  Init();
}

void BalanceLabel::Init() {
  coins_sprite_.setTexture(State::GetTextureResourceManager().
      GetOrLoadResource("assets/ui/coins.png"));
  double max_side = std::max(
      coins_sprite_.getGlobalBounds().height, coins_sprite_.getGlobalBounds().width);
  coins_sprite_.setScale(20 / max_side, 20 / max_side);
  coins_sprite_.setPosition(x_, y_);
  text_.setFont(State::GetFontResourceManager()
                    .GetOrLoadResource("assets/font/default.ttf"));
  text_.setCharacterSize(20);
  text_.setPosition(x_ + 20, y_);
  text_.setString(std::to_string(balance_));
}

void BalanceLabel::Save(std::ostream& out) {
  out << x_ << " " << y_ << std::endl;
  out << balance_ << std::endl;
}

void BalanceLabel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  target.draw(coins_sprite_, states);
  target.draw(text_, states);
}

int BalanceLabel::GetBalance() const {
  return balance_;
}

void BalanceLabel::ChangeBalance(int delta) {
  balance_ += delta;
  text_.setString(std::to_string(balance_));
}
