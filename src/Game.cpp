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

}


Player Game::turn(){
int currentrow = 7;
int totalred = 0;
int totalgreen = 0;
Player res;

for (int i = 0; i<6; i++){
	currentrow = 7;
	for(int j = 0; j<7; j++){
	if(this->get(i,j) == BS_RED) totalred++;
	if(this->get(i,j) == BS_GREEN) totalgreen++;
	else currentrow--;
	if (currentrow == 0) i = 6;
	}
}
if (totalred >= totalgreen && this->starter == GREEN) res = GREEN;
else res = RED;

return res;
}

Player Game::who_win(){

}

bool Game::is_over(){}

CONNECT4_ERROR Game::is_valid() const{

}

bool Game::operator==(const Game &other) const{

}

CONNECT4_ERROR Game::apply(Move m){

}
