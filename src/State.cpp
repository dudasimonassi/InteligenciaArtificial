#include <iostream>
#include <vector>
#include <chrono>
#include <stack>
#include <list>
#include <queue>
#include <unordered_set>
#include <set>
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

int State::getSize(){

    return this->board->getSize();

}

std::vector<State*> State::getParents(){
    
    return this->parents;

}

string State::getMovement(){

    return this->movement;

}

void State::setLastParent(State* parent){

    this->parents.push_back(parent);

}

void State::setMovement(string movement){

    this->movement = movement;

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

std::vector<State*> State::generateChildStates() {
    int zeroX = this->board->getZeroPosition()[0];
    int zeroY = this->board->getZeroPosition()[1];

    std::vector<State*> childStates;

    for (const std::string& movement : movements) {
        State* childState = new State(this->board->getBoardCopy(), this->finalState, this->parents);
        childState->getParents().push_back(this);
        
        if (movement == "Up") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX - 1, zeroY);
            childState->setMovement("Up");
        } else if (movement == "Down") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX + 1, zeroY);
            childState->setMovement("Down");
        } else if (movement == "Left") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX, zeroY - 1);
            childState->setMovement("Left");
        } else if (movement == "Right") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX, zeroY + 1);
            childState->setMovement("Right");
        }
        
        childStates.push_back(childState);
    }

    return childStates;
}

void State::backtracking(){
   
}

void State::bfs() { //Busca em Largura -> busca sempre o estado mais antigo 
    std::queue<State*> openStates; //Lista de estados abertos
    std::unordered_set<State*> closedStates; //Lista de estados fechados (todos os filhos foram gerados)
    int childState = 0;

    openStates.push(this); //Adiciona o estado inicial a lista de abertos

    while (!openStates.empty()) {
        State* currentState = openStates.front(); //Primeiro estado da lista vira o estado atual

        if (currentState->isFinalState()) { //Verifica se atingiu o estado final 
            cout << endl << "End of the search." << endl;
            cout << endl << "Movements: " << endl;            
            if(!currentState->getParents().empty()){
                for (State* parent : currentState->getParents()) { 
                    parent->getBoard()->printBoard();
                    cout << endl;
                }
            }
            currentState->getBoard()->printBoard();
            cout << endl << "Solution depth: " << currentState->getParents().size() << endl; 
            cout << "Solution cost: " << closedStates.size() + openStates.size() << endl;
            cout << "Expanded nodes: " << closedStates.size() << endl;
            cout << "Visited nodes: " << closedStates.size() + openStates.size() << endl;
            cout << "Average branching factor value: " << static_cast<double> (childState) / closedStates.size() << endl;
            return;
        }

        currentState->possibleMovements(); //Verifica os possiveis movimentos 

        std::vector<State*> childStates = currentState->generateChildStates(); //Geração dos filhos 

        childState =  childState + childStates.size(); 

        openStates.pop();  //Estado removido da fila de estados abertos 
        closedStates.insert(currentState);  //Inserção na lista de fechados _ filhos já foram gerados 

        if(!currentState->getParents().empty()){
            for (State* parent : currentState->getParents()) { //Para cada filho gerado verifica se o mesmo não é pai do estado atual
                for(State* childState : childStates){
                    if(childState->isEqualState(parent)){
                            vector<State*>::iterator new_end = std::remove(childStates.begin(), childStates.end(), childState);
                            childStates.erase(new_end, childStates.end());
                    }
                }
            }
        }

        if(!childStates.empty()){ 

            for (State* childState : childStates) { //Para cada filho gerado, verifica se o mesmo já é um estado fechado 
                if (closedStates.find(childState) == closedStates.end()) { //Não é um estado fechado
                    childState->setLastParent(currentState); //Atualiza a lista de pais 
                    openStates.push(childState); // Adiciona o filho na fila
                }
            }
        }
    }
}

void State::dfs(){  //Busca em Profundidade -> busca sempre o estado mais novo
    std::stack<State*> openStates; //Pilha de estados abertos
    std::unordered_set<State*> closedStates; //Lista de estados fechados (todos os filhos foram gerados)
    int childState = 0; // Controle da quantidade de filhos para gerar o fator médio de ramificação 

    openStates.push(this); //Adiciona o estado inicial a pilha de abertos

    while (!openStates.empty()) {
        State* currentState = openStates.top(); //Primeiro estado da pilha vira o estado atual

        if (currentState->isFinalState()) { //Verifica se atingiu o estado final 
            cout << endl << "End of the search." << endl;
            cout << endl << "Movements: " << endl;            
            if(!currentState->getParents().empty()){
                for (State* parent : currentState->getParents()) { 
                    parent->getBoard()->printBoard();
                    cout << endl;
                }
            }
            currentState->getBoard()->printBoard();
            cout << endl << "Solution depth: " << currentState->getParents().size() << endl; 
            cout << "Solution cost: " << closedStates.size() + openStates.size() << endl;
            cout << "Expanded nodes: " << closedStates.size() << endl;
            cout << "Visited nodes: " << closedStates.size() + openStates.size() << endl;
            cout << "Average branching factor value: " << static_cast<double> (childState) / closedStates.size() << endl;
            return;
        }

        currentState->possibleMovements(); //Verifica os possiveis movimentos 

        std::vector<State*> childStates = currentState->generateChildStates(); //Geração dos filhos 

        childState =  childState + childStates.size(); 

        openStates.pop();  //Estado removido da pilha de estados abertos 
        closedStates.insert(currentState);  //Inserção na lista de fechados _ filhos já foram gerados 

        if(!currentState->getParents().empty()){
            for (State* parent : currentState->getParents()) { //Para cada filho gerado verifica se o mesmo não é pai do estado atual
                for(State* childState : childStates){
                    if(childState->isEqualState(parent)){
                            vector<State*>::iterator new_end = std::remove(childStates.begin(), childStates.end(), childState);
                            childStates.erase(new_end, childStates.end());
                    }
                }
            }
        }

        if(!childStates.empty()){ 

            for(int i = (childStates.size()-1); i >= 0; i--){ //Para manter a lógica da estratégia de controle 
                if(closedStates.find(childStates[i]) == closedStates.end()){
                    childStates[i]->setLastParent(currentState); //Atualiza a lista de pais 
                    openStates.push(childStates[i]); // Adiciona o filho na pilha
                }
            }
        }
    }

}

void State::ordered(){



}

void State::greedy(){


}

void State::aStar(){


}

void State::idaStar(){

}

int State::cost(){ // O custo será calculado pela quantidade de peças fora do lugar 

    int cost = 0;

    for(int i = 0; i < this->board->getSize(); i++){

        for(int j =0; j < this->board->getSize(); j++){

            if(this->board->getPiece(i,j)->getValue() != this->finalState->getBoard()->getPiece(i,j)->getValue()){
                cost++;
            }

        }

    }

    return cost;

}

int State::heuristic(){ //A heurística é calculada pela soma das distância de manhattan

    int cost = 0;
    int pieceValue;

    for(int i = 0; i < this->board->getSize(); i++){

        for(int j =0; j < this->board->getSize(); j++){

            pieceValue = this->getBoard()->getPiece(i,j)->getValue();

            cost = cost + (abs((this->getFinalState()->getBoard()->getPosition(pieceValue)[0] - this->getBoard()->getPiece(i,j)->getPosition()[0])) + abs(this->getFinalState()->getBoard()->getPosition(pieceValue)[1]- this->getBoard()->getPiece(i,j)->getPosition()[1]));

        }

    }

    return cost;


}