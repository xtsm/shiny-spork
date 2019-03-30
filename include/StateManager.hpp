#pragma once
#include <MainMenuState.hpp>
#include <GameState.hpp>

class StateManager {
 public:
  StateManager();
  ~StateManager();
  State* GetActiveState();
  void ChangeState(State* state);
  bool Closed();
  void Close();
  MainMenuState* main_menu;
  GameState* game;
  State* active_state;
 protected:
  bool closed_;
 private:
  StateManager(const StateManager&) = delete;
  StateManager& operator=(const StateManager&) = delete;
};
