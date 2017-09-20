#pragma once
#include <iostream>
#include <vector>

struct Game;
struct Move;

enum Player{
  RED,
  GREEN,
  NO_ONE
};


enum Board_state{
  BS_RED,
  BS_GREEN,
  EMPTY
};

Board_state Player_to_Board_state(Player player);
Player Board_state_to_Player(Board_state bs);


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
  CONNECT4_ERROR is_valid() const;
};

struct Game
{
  Board_state data[6][7];
  Player starter;
  Player current_turn;

  Game(Player starter=RED);

  void set(unsigned int row, unsigned column,Board_state state);
  Board_state get(unsigned int row, unsigned column) const;
  
  unsigned int total_chips() const;

  Player who_win() const;


  void set_turn(Player p);
  Player get_turn() const;


  bool is_over() const;

  CONNECT4_ERROR is_valid() const;

  bool operator==(const Game &other) const;

  CONNECT4_ERROR apply(Move m);
  CONNECT4_ERROR play(unsigned int row);
  CONNECT4_ERROR play(std::vector<unsigned int> const &rows);

  private:
  bool is_valid_gravity() const;
  bool is_valid_turn_parity() const;
  int get_first_empty_space(int column);
};

std::ostream& operator<<(std::ostream& os, const Game& c);
