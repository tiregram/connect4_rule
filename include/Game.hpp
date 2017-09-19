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

enum CONNECT4_ERROR{
  OK,
  POSITION,
  WRONG_TURN,
  GRAVITY,
  FULL_COLUMN,
  TURN_PARITY

  //...
};

struct Move
{
  Move(unsigned int column,Player player,Game& g);
  unsigned int column;
  Player player;
  Game& g;
  CONNECT4_ERROR is_valid();
};

struct Game
{
  Board_state data[6][7];
  Player starter;

  Game(Player starter=RED);

  void set(unsigned int row, unsigned column,Board_state state);
  Board_state get(unsigned int row, unsigned column);

  unsigned int total_chips();

  Player turn(); // TODO remove this one for get_turn

  void set_turn(Player p);
  Player get_turn();

  Player who_win();

  bool is_over();

  CONNECT4_ERROR is_valid() const;

  bool operator==(const Game &other) const;

  CONNECT4_ERROR apply(Move m);
  CONNECT4_ERROR play(unsigned int row);
  CONNECT4_ERROR play(unsigned int rows[]);


};

std::ostream& operator<<(std::ostream& os, const Game& c);
