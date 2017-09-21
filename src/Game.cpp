#include "../include/Game.hpp"

/*
Implementation of game mechanics and rules of Connect4 for NAO.
Project by EPS group I: Marveen Parras, Arthur Margerit and Derek Burrell.
*/

//Function to switch from Player to Board_state
Board_state Player_to_Board_state(Player player){
	switch(player){
		case RED:return BS_RED;break;
		case GREEN:return BS_GREEN;break;
		case NO_ONE:throw(std::string("Invalid conversion NO_ONE"));break;
		}
	return EMPTY;
}

//Function to switch from Board_state to Player
Player Board_state_to_Player(Board_state bs){
	switch(bs){
		case BS_RED:return RED;break;
		case BS_GREEN:return GREEN;break;
		case EMPTY:throw(std::string("Invalid conversion EMPTY"));break;
	}
	return NO_ONE;
}

//Default constructor of Move
Move::Move(unsigned int column,Player player,Game& g):column(column),player(player),g(g){
}

//Checks if Move is valid. Returns POSITION if the column is not valid, FULL_COLUMN if the column is full, WRONG_TURN if it's not the correct player, and OK if the play is valid.
CONNECT4_ERROR Move::is_valid() const{
	if(column>6) return POSITION;
	if(g.get(5,column) != EMPTY) return FULL_COLUMN;
	if(g.get_turn() != player) return WRONG_TURN;
	return OK;
}

//Default constructor of Game. Fills the board with EMPTY state.
Game::Game(Player starter):starter(starter),current_turn(starter){
	for (int i = 0; i<6; i++){
		for(int j = 0; j<7; j++){
			data[i][j]=EMPTY;
		}
	}
}

//Set for position states
void Game::set(unsigned int row, unsigned column,Board_state state){
	data[row][column] = state;
}

//Get for position states
Board_state Game::get(unsigned int row, unsigned column) const{
	return data[row][column];
}

//Set for curent turn
void Game::set_turn(Player player){
  	current_turn = player;
}

//Get for current turn
Player Game::get_turn() const{
	return current_turn;
}

//Function to calculate total number of chips in-game
unsigned int Game::total_chips() const{
	int res = 0;
	int current_row = 7;
	for (int i = 0; i<6; i++){
		current_row = 7;
		for(int j = 0; j<7; j++){
			if(this->get(i,j) != EMPTY) res++;
			else current_row--;
			if (current_row == 0) i = 6;
		}
	}
	return res;
}

//Function to check if someone has won. 
Player Game::who_win() const{
//Vertical check
	for (int i = 0; i<3; i++){
		for(int j = 0; j<7; j++){
			if(	(data[i  ][j] != EMPTY) &&
				(data[i  ][j] == data[i+1][j]) &&
				(data[i+2][j] == data[i+3][j]) &&
				(data[i  ][j] == data[i+2][j])){
				return Board_state_to_Player(data[i][j]);
			}
		} 
	}
//Horizontal check
	for (int i = 0; i<6; i++){
		for(int j = 0; j<4; j++){
			if(	(data[i  ][j] != EMPTY) &&
				(data[i  ][j] == data[i][j+1]) &&
				(data[i][j+2] == data[i][j+3]) &&
				(data[i  ][j] == data[i][j+2])){
				return Board_state_to_Player(data[i][j]);
			}
		}
	}
//Diagonal Ascending Check
	for (int i = 0; i<3; i++){
		for(int j = 0; j<4; j++){
			if(	(data[i][j] != EMPTY) &&
				(data[i  ][j  ] == data[i+1][j+1]) &&
				(data[i+2][j+2] == data[i+3][j+3]) &&
				(data[i+1][j+1] == data[i+3][j+3])){
				return Board_state_to_Player(data[i][j]);
				//If they all have the same color, return
			}
			
		}
	}
//Diagonal Descending Check
	for (int i = 0; i<3; i++){
		for(int j = 3; j<7; j++){
			if(	(data[i][j] != EMPTY) &&
				(data[i  ][j  ] == data[i+1][j-1]) &&
				(data[i+2][j-2] == data[i+3][j-3]) &&
				(data[i+1][j-1] == data[i+3][j-3])){
				return Board_state_to_Player(data[i][j]);
				//If they all have the same color, return
			}
			
		}
	}
	return NO_ONE;
}

//Check if game is over.
bool Game::is_over() const{
	Player winner = this->who_win();
	if(	winner == RED || 
		winner == GREEN || 
		(winner == NO_ONE &&
		 this->total_chips() == 42))
		  return true;
	return false;
}

//Check if no impossible case of chip being over an empty spot is on the current board(will be useful to confirm NAO vision read)
bool Game::is_valid_gravity() const{
	for(int j = 0; j<7; j++){
		bool found_empty = false;
		for (int i = 0; i<6; i++){
			//If we already found an empty spot, we check if there is something over it not empty
			if(found_empty == true && data[i][j] != EMPTY) return false;
			//Find the first empty spot
			if(found_empty == false && data[i][j] == EMPTY)found_empty=true;
		}
	}
		
	return true;
}

//Check if the turns have been respected and the current board has a normal state.
bool Game::is_valid_turn_parity() const{
	int res_green = 0;
	int res_red = 0;
	int current_row = 7;

	for (int i = 0; i<6; i++){
		current_row = 7;
		for(int j = 0; j<7; j++){
			if(this->get(i,j) == BS_RED) res_red++;
			else if (this->get(i,j) == BS_GREEN) res_green++;
			else current_row--;
		if (current_row == 0) i = 6;
		}
	}
	if (this->starter == RED && (res_red < res_green)) return false;
	if (this->starter == RED && this->current_turn == RED && (res_red > res_green)) return false;
	if (this->starter == RED && this->current_turn == GREEN && (res_red <= res_green)) return false;
	if (this->starter == GREEN && (res_red > res_green)) return false;
	if (this->starter == GREEN && this->current_turn == GREEN && (res_red < res_green)) return false;
	if (this->starter == GREEN && this->current_turn == RED && (res_red >= res_green)) return false;
	if (res_red - res_green > 2 || res_red - res_green < -2 ) return false;
	return true;
}

//Checks if both gravity and parity are respected
CONNECT4_ERROR Game::is_valid() const{
	if (!is_valid_gravity()) return GRAVITY;
	if (!is_valid_turn_parity()) return TURN_PARITY;		
	return OK;
}

//Compares two boards. They are only considered equal if the same player has started and the exact same positions are filled.
bool Game::operator==(const Game &other) const{
	if (starter != other.starter){
		return false;
	}

	for (int i = 0; i<6; i++){
			for(int j = 0; j<7; j++){
				if (data[i][j] != other.data[i][j]){
					return false;
				}
			}
	}
	return true;
}

//Required to check which is the first space the chip can be stored
int Game::get_first_empty_space(int column){

	for (int i = 0; i<6; i++){
		if(data[i][column] == EMPTY) return i;	
		}
	return -1;
}

//Applies a move, checking if the move and the game are valid before doing so. 
CONNECT4_ERROR Game::apply(Move m){

	CONNECT4_ERROR game_valid = this->is_valid();
	CONNECT4_ERROR move_valid = m.is_valid();
	
	if (game_valid == OK && move_valid == OK){
		
		data[get_first_empty_space(m.column)][m.column] = Player_to_Board_state(m.player);
		if (get_turn() == RED) set_turn(GREEN);
		else set_turn(RED);
	}
	else if (move_valid != OK) return move_valid;
	else if (game_valid != OK) return game_valid;

	return OK;
}

//Function to compare two boards, to know if the other board could be a continuation of the implicit board.
bool Game::possible_posterior_game(const Game &other) const{
	if(starter != other.starter) return false;
	for (int i = 0; i<6; i++){
		for(int j = 0; j<7; j++){
			if(get(i,j) != EMPTY && other.get(i,j) == EMPTY) return false;
			if(get(i,j) == BS_RED && other.get(i,j) == BS_GREEN) return false;
			if(get(i,j) == BS_GREEN && other.get(i,j) == BS_RED) return false;
		}
	}
	return true;
}

//Testing function to just play on a specific column without caring whose turn it is.
CONNECT4_ERROR Game::play(unsigned int column){
	Move m(column,get_turn(),*this);
	return apply(m);
}

//Testing function to do multiple plays in a row
CONNECT4_ERROR Game::play(std::vector<unsigned int> const &columns){
	for(unsigned int i = 0; i<columns.size(); i++){
		CONNECT4_ERROR error = play(columns[i]);
		if (error != OK) return error;
	}
	return OK;
}

//Testing function to output the current game on the terminal
std::ostream& operator<<(std::ostream& os, const Game& c){
	os << "Game starter: "<<c.starter<<" Current turn: "<< c.current_turn << std::endl;
	for (int i = 5; i>-1;i--){
  		os << std::endl << "|";
  		for (int j = 0; j<7;j++){
  			os << c.get(i,j) << "|";
  		}
  	}
  	os << std::endl;
  	return os;
}
