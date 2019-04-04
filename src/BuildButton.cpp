#include <GameState.h>
#include "BuildButton.h"

BuildButton::BuildButton(GameState& game_state, int x, int y) :
    Button(game_state, x, y, "Build"),
    game_state_(game_state) {
}

void BuildButton::Click() {
  game_state_.BuildMenu();
}

