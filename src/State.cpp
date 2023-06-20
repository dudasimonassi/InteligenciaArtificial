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

Board* State::getBoard(){

    return this->board;

}

State* State::getFinalState(){

    return this->finalState;

}

int State::getSize(){

    return this->board->getSize();

}

bool State::isFinalState(){

    for(int i = 0; i < this->board->getSize(); i++){

        for(int j =0; j < this->board->getSize(); j++){

            if(this->board->getPiece(i,j)->getValue() != this->finalState->getBoard()->getPiece(i,j)->getValue()){
                return false;
            }

        }

    }

    return true;

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

bool State::isPossible(){

    int initialStateInversions = 0;
    int finalStateInversions = 0;
    int size =  this->getSize();

    for (int i = 0; i < size * size - 1; i++) {

        for (int j = i + 1; j < size * size; j++) {

            Piece* current = this->getBoard()->getPiece((i/size),(i%size));
            Piece* next = this->getBoard()->getPiece((j/size),(j%size));

            if ((current->getValue() != 0 && next->getValue() != 0) && current->getValue() > next->getValue()) {
                initialStateInversions++;
            }
        }
    }

    for (int i = 0; i < size * size - 1; i++) {

        for (int j = i + 1; j < size * size; j++) {

            Piece* current = this->finalState->getBoard()->getPiece((i/size),(i%size));
            Piece* next = this->finalState->getBoard()->getPiece((j/size),(j%size));

            if ((current->getValue() != 0 && next->getValue() != 0) && current->getValue() > next->getValue()) {
                finalStateInversions++;
            }
        }
    }

    if((finalStateInversions % 2 == 0 && initialStateInversions % 2 == 0) || (finalStateInversions % 2 != 0 && initialStateInversions % 2 != 0) )
        return true;

    else    
        return false;

}