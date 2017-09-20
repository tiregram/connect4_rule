#include "../include/Game.hpp"





Board_state Player_to_Board_state(Player player){
	switch(player){
		case RED:return BS_RED;break;
		case GREEN:return BS_GREEN;break;
		case NO_ONE:throw(std::string("Invalid conversion NO_ONE"));break;
		}
	return EMPTY;
}

Player Board_state_to_Player(Board_state bs){
	switch(bs){
		case BS_RED:return RED;break;
		case BS_GREEN:return GREEN;break;
		case EMPTY:throw(std::string("Invalid conversion EMPTY"));break;
	}
	return NO_ONE;
}



Move::Move(unsigned int column,Player player,Game& g):column(column),player(player),g(g){
}

CONNECT4_ERROR Move::is_valid() const{

	CONNECT4_ERROR res = OK;
	if(column>6) res = POSITION;
	else if(g.get(5,column) != EMPTY) res = FULL_COLUMN;
	else if(g.get_turn() != player) res = WRONG_TURN;

	return res;
}


Game::Game(Player starter):starter(starter),current_turn(starter){
	for (int i = 0; i<6; i++){
		for(int j = 0; j<7; j++){
			data[i][j]=EMPTY;
		}
	}
}

void Game::set(unsigned int row, unsigned column,Board_state state){
	data[row][column] = state;
}

Board_state Game::get(unsigned int row, unsigned column) const{
	return data[row][column];
}

void Game::set_turn(Player player){
  	current_turn = player;
}
Player Game::get_turn() const{
	return current_turn;
}

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


/*Player Game::turn() const{
	int chips = this->total_chips();
	int mod = chips%2;
	Player res;
	if (mod == 0) res = this->starter;
	else if (this->starter == RED && mod == 1) res = GREEN;
	else res = RED;
	return res;
}*/

Player Game::who_win() const{
//vertical
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
//horizontal
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

//diagonal ascending
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
//diagonal descending
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

bool Game::is_over() const{
	if(	this->who_win() == RED || 
		this->who_win() == GREEN || 
		(this->who_win() == NO_ONE &&
		 this->total_chips() == 42))
		  return true;
	return false;
}

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

CONNECT4_ERROR Game::is_valid() const{
	if (!is_valid_gravity()) return GRAVITY;
	if (!is_valid_turn_parity()) return TURN_PARITY;		
	return OK;
}

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

//Requires 
int Game::get_first_empty_space(int column){

	for (int i = 0; i<6; i++){
		if(data[i][column] == EMPTY) return i;	
		}
	return -1;
}

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

CONNECT4_ERROR Game::play(unsigned int row){
	Move m(row,get_turn(),*this);
	return apply(m);
}
CONNECT4_ERROR Game::play(std::vector<unsigned int> const &rows){
	for(unsigned int i = 0; i<rows.size(); i++){
		CONNECT4_ERROR error = play(rows[i]);
		if (error != OK) return error;
	}
	return OK;
}

std::ostream& operator<<(std::ostream& os, const Game& c)
{
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
