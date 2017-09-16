#include "../include/Game.hpp"




Move::Move(unsigned int column,Player player,Game& g):column(column),player(player),g(g){
}

CONNECT4_ERROR Move::is_valid(){

CONNECT4_ERROR res = OK;
if(column>6) res = POSITION;
else if(g.get(5,column) != EMPTY) res = FULL_COLUMN;
else if(g.turn() != player) res = WRONG_TURN;

return res;
}


Game::Game(Player starter):starter(starter){

}

void Game::set(unsigned int row, unsigned column,Board_state state){
data[row][column] = state;
}

Board_state Game::get(unsigned int row, unsigned column){
return data[row][column];
}

unsigned int Game::total_chips(){
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


Player Game::turn(){
int chips = this->total_chips();
int mod = chips%2;
Player res;
if (mod == 0) res = this->starter;
else if (this->starter == RED && mod == 1) res = GREEN;
else res = RED;


return res;
}

Player Game::who_win(){
Player winner = NO_ONE;
//vertical
for (int i = 0; i<4; i++){
	for(int j = 0; j<6; j++){
		if(data[i][j] == BS_RED && data[i+1][j] == BS_RED && data[i+2][j] == BS_RED && data[i+3][j] == BS_RED) winner = RED;
		else if(data[i][j] == BS_GREEN && data[i+1][j] == BS_GREEN && data[i+2][j] == BS_GREEN && data[i+3][j] == BS_GREEN) winner = GREEN;
	}
} 

//horizontal
for (int i = 0; i<3; i++){
	for(int j = 0; j<7; j++){
		if(data[i][j] == BS_RED && data[i][j+1] == BS_RED && data[i][j+2] == BS_RED && data[i][j+3] == BS_RED) winner = RED;
		else if(data[i][j] == BS_GREEN && data[i][j+1] == BS_GREEN && data[i][j+2] == BS_GREEN && data[i][j+3] == BS_GREEN) winner = GREEN;
	}
} 

//diagonal1
for (int i = 3; i<7; i++){
	for(int j = 0; j<3; j++){
		if(data[i][j] == BS_RED && data[i-1][j+1] == BS_RED && data[i-2][j+2] == BS_RED && data[i-3][j+3] == BS_RED) winner = RED;
		else if(data[i][j] == BS_GREEN && data[i-1][j+1] == BS_GREEN && data[i-2][j+2] == BS_GREEN && data[i-3][j+3] == BS_GREEN) winner = GREEN;
	}
}
//diagonal2
for (int i = 3; i<7; i++){
	for(int j = 3; j<6; j++){
		if(data[i][j] == BS_RED && data[i-1][j-1] == BS_RED && data[i-2][j-2] == BS_RED && data[i-3][j-3] == BS_RED) winner = RED;
		else if(data[i][j] == BS_GREEN && data[i-1][j-1] == BS_GREEN && data[i-2][j-2] == BS_GREEN && data[i-3][j-3] == BS_GREEN) winner = GREEN;
	}
}
return winner;



}

bool Game::is_over(){
bool res=false;
if(this->who_win() == RED || this->who_win() == GREEN || (this->who_win() == NO_ONE && this->total_chips() == 42)) res = true;
return res;
}

CONNECT4_ERROR Game::is_valid() const{
		

}

bool Game::operator==(const Game &other) const{

bool res = (starter == other.starter);
while (res){
	for (int i = 0; i<7; i++){
		for(int j = 0; j<6; j++){
		res = (data[i][j] == other.data[i][j]);
}
}
}
return res;
}

CONNECT4_ERROR Game::apply(Move m){

CONNECT4_ERROR res=OK;
int i=0;
Board_state b;

if (m.player == RED) b = BS_RED;
else b = BS_GREEN;
if (this->is_valid() && m.is_valid()){
while (data[i][m.column] != EMPTY){
 i++;
}

data[i][m.column] = b;
}
return res;
}
