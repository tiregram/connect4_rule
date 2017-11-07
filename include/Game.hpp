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
  EMPTY,
  BS_RED,
  BS_GREEN
};

Board_state player_to_board_state(Player player);
Player board_state_to_Player(Board_state bs);
std::string player_name(Player player);
Player opposite_player(Player player);

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
private:
  Board_state data[6][7];
  Player starter;
  Player current_turn;

public:
  //constructor
  Game(Player starter=RED);
  
  //copy constructor
  Game(const Game &g);

  // get and set

  void set(unsigned int row, unsigned column,Board_state state);
  Board_state get(unsigned int row, unsigned column) const;

  bool is_column_full(int column) const;
  unsigned int total_chips() const;

  Player who_win() const;

  void set_turn(Player player);
  Player get_turn() const;
  
  // test
  bool is_over() const;
  CONNECT4_ERROR is_valid() const;

  bool operator==(const Game &other) const;
  bool possible_posterior_game(const Game &other) const;

  int get_first_empty_space(int column);
  // play
  CONNECT4_ERROR apply(Move m);
  CONNECT4_ERROR play(unsigned int column);
  CONNECT4_ERROR play(std::vector<unsigned int> const &columns);

  private:
  bool is_valid_gravity() const;
  bool is_valid_turn_parity() const;

};

std::ostream& operator<<(std::ostream& os, const Game& c);
