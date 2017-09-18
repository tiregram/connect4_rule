#pragma once
#include <iostream>

struct Game;
struct Move;

enum Player{
  RED,
  GREEN,
  NO_ONE,
};


enum Board_state{
  EMPTY,
  BS_RED,
  BS_GREEN
};

Board_state Player_to_Board_state(Player player);
Player Board_state_to_Player(Board_state bs);


enum CONNECT4_ERROR{
  OK,
  POSITION,
  WRONG_TURN,
  GRAVITY,
  FULL_COLUMN,
  WRONG_PARITY	

  //...
};

struct Move
{
  Move(unsigned int column,Player player,Game& g);
  unsigned int column;
  Player player;
  Game& g;
  CONNECT4_ERROR is_valid() const;
};

struct Game
{
  Board_state data[6][7];
  Player starter;

  Game(Player starter=RED);

  void set(unsigned int row, unsigned column,Board_state state);
  Board_state get(unsigned int row, unsigned column) const;

  unsigned int total_chips() const;

  Player turn() const; 

  Player who_win() const;

  bool is_over() const;

  CONNECT4_ERROR is_valid() const;

  bool operator==(const Game &other) const;

  CONNECT4_ERROR apply(Move m);
  CONNECT4_ERROR play(unsigned int row);
  CONNECT4_ERROR play(unsigned int rows[]);

  private:
  bool is_valid_gravity() const;
  bool is_valid_turn_parity() const;
};

std::ostream& operator<<(std::ostream& os, const Game& c);
