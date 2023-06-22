#include <iostream>
#include <vector>
#include <chrono>
#include <stack>
#include <list>
#include <algorithm>
#include "../include/Piece.h"
#include "../include/Board.h"
#include "../include/State.h"

using namespace std;

State::State(Board *board, State *finalState, std::vector<State*> parents){

    this->board = board;

    this->finalState = finalState;

    this->parents = parents;

}

State::State(Board *board){

    this->board = board;

}


Board* State::getBoard(){

    return this->board;

}

State* State::getFinalState(){

    return this->finalState;

}

int State::getDepth(){

    return this->depth;

}

int State::getSize(){

    return this->board->getSize();

}

std::vector<State*> State::getParents(){
    
    return this->parents;

}

std::vector<string> State::getPath(){

    return this->path;

}

double State::getBranchingFactorSum(){

    return this->branchingFactorSum;

}

int State::getNodeCount(){
    
    return this->nodeCount;

}

int State::getExpandedCount(){

    return this->expandedCount;

}

int State::getVisitedCount(){

    return this->visitedCount;

}

void State::setLastParent(State* parent){

    this->getParents().push_back(parent);

}

void State::setBranchingFactorSum(double branchingFactorSumIncrement){

    this->branchingFactorSum += branchingFactorSumIncrement;

}
        
void State::setNodeCount(int nodeCountIncrement){

    this->nodeCount += nodeCountIncrement;

}
        
void State::setExpandedCount(int expandedCountIncrement){

    this->expandedCount += expandedCountIncrement;

}
        
void State::setVisitedCount(int visitedCountIncrement){

    this->visitedCount += visitedCountIncrement;

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

bool State::isEqualState(State *state){

    for(int i = 0; i < this->board->getSize(); i++){

        for(int j =0; j < this->board->getSize(); j++){

            if(this->board->getPiece(i,j)->getValue() != state->getBoard()->getPiece(i,j)->getValue()){
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

    for (int i = 0; i < (size * size - 1); i++) {

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

void State::backtracking(State * initialState){

    while(!this->isFinalState()){

        this->possibleMovements();

        if(!this->movements.empty()){

            string move = this->movements[0];

            int zeroRow = this->getBoard()->getZeroPosition()[0];
            int zeroColumn = this->getBoard()->getZeroPosition()[0];

            Piece *zeroPiece = new Piece(0, zeroRow, zeroColumn);

            if(move == "Up"){
                Piece *movingPiece = new Piece(this->getBoard()->getPiece(zeroRow-1, zeroColumn)->getValue(), zeroRow, zeroColumn); 

                this->board->setPiece(movingPiece, zeroRow, zeroColumn);
                this->board->setPiece(zeroPiece, zeroRow-1, zeroColumn);

                this->path.push_back(move);

            }
            else if(move == "Down"){
                Piece *movingPiece = new Piece(this->getBoard()->getPiece(zeroRow+1, zeroColumn)->getValue(), zeroRow, zeroColumn); 

                this->board->setPiece(movingPiece, zeroRow, zeroColumn);
                this->board->setPiece(zeroPiece, zeroRow+1, zeroColumn);

                this->path.push_back(move);

            }
            else if(move == "Left"){
                Piece *movingPiece = new Piece(this->getBoard()->getPiece(zeroRow, zeroColumn-1)->getValue(), zeroRow, zeroColumn); 

                this->board->setPiece(movingPiece, zeroRow, zeroColumn);
                this->board->setPiece(zeroPiece, zeroRow, zeroColumn-1);

                this->path.push_back(move);           
            }
            else if(move == "Right"){
                Piece *movingPiece = new Piece(this->getBoard()->getPiece(zeroRow, zeroColumn+1)->getValue(), zeroRow, zeroColumn); 

                this->board->setPiece(movingPiece, zeroRow, zeroColumn);
                this->board->setPiece(zeroPiece, zeroRow, zeroColumn+1);

                this->path.push_back(move);            
            }

        }

        else{

            if(this->isEqualState(initialState)){

                cout << "Search failure. There is no solution.";
                exit(1);

            }

            else{

                

            }

        }

    }

    cout << "End of the serach. " << endl;

    if(!this->path.empty()){

        cout << "Path:";
        for(int i = 0; i < (this->path.size() -1) ; i++){
            cout << this->getPath()[i] << " -> ";
        }
        cout << this->getPath()[this->path.size() -1] << endl;
        
    }

    cout << "Depth:" << this->getDepth() << endl;

    double averageBranchingFactor = this->getBranchingFactorSum() / this->getNodeCount();
    cout << "Average Branching Factor: " << averageBranchingFactor << endl;

}

void State::bfs(){


}

void State::dfs(){


}

void State::ordered(){


}

void State::greedy(){


}

void State::aStar(){


}

void State::idaStar(){


}