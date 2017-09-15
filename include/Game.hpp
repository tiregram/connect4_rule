#pragma once


struct Game;
struct Move;

enum Winner{
  RED,
  GREEN,
  NO_ONE,
  DRAW
};


enum Board_state{
  EMPTY,
  RED,
  GREEN
};

enum CONNECT4_ERROR{
  OK,
  POSITION,
  TURN_PARITY,
  GRAVITY,

  //...
};

struct Move
{
  Move(unsigned int column,Board_state player,Game& g);
  unsigned int column;
  Board_state player;
  CONNECT4_ERROR is_valid();
};

struct Game
{
  Board_state data[6][7];

  Game();

  void set(unsigned int row, unsigned column,Board_state state);
  Board_state get(unsigned int row, unsigned column);

  Winner who_win();

  CONNECT4_ERROR is_valid() const;

  bool operator==(const Game &other) const;

  CONNECT4_ERROR apply(Move m);

};
