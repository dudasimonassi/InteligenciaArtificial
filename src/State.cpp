#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Piece.h"
#include "../include/Board.h"
#include "../include/State.h"

using namespace std;

State::State(Board *board, State *finalState, std::vector<State> parents){

    this->board = board;

    this->finalState = finalState;

    this->parents = parents;

}

bool State::isFinalState(){

    if(this->board == this->finalState->board)
        return true;
    
    return false;


}

void State::possibleMovements(){

    if(this->board->getZeroPosition()[1] == ((this->board->getSize())-1)){

        auto it = std::find(movements.begin(), movements.end(), "Right");
        if (it != movements.end()) {
            movements.erase(it);
        }
    }

    if(this->board->getZeroPosition()[1] == 0){

        auto it = std::find(movements.begin(), movements.end(), "Left");
        if (it != movements.end()) {
            movements.erase(it);

        }
    }

    if(this->board->getZeroPosition()[0] == ((this->board->getSize())-1)){

        auto it = std::find(movements.begin(), movements.end(), "Down");
        if (it != movements.end()) {
            movements.erase(it);

        }
    }

    if(this->board->getZeroPosition()[0] == 0){

        auto it = std::find(movements.begin(), movements.end(), "Up");
        if (it != movements.end()) {
            movements.erase(it);

        }
    }

}

void State::createChildren(){

}

Board* State::getBoard(){

    return this->board;

}