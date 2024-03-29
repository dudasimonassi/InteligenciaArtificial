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

// Funções de Ordenação para o algoritmo de busca ordenada
void mergeOrdered(std::vector<State*>& list, int begin, int mid, int end) {
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    std::vector<State*> left(n1);
    std::vector<State*> right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = list[begin + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = list[mid + 1 + j];
    }

    int i = 0;  
    int j = 0;  
    int k = begin;  

    while (i < n1 && j < n2) {
        if (left[i]->cost() <= right[j]->cost()) {
            list[k] = left[i];
            i++;
        } else {
            list[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        list[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        list[k] = right[j];
        j++;
        k++;
    }
}

void mergeSortOrdered(std::vector<State*>& list, int begin, int end) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;

        mergeSortOrdered(list, begin, mid);

        mergeSortOrdered(list, mid + 1, end);

        mergeOrdered(list, begin, mid, end);
    }
}

// Funções de Ordenação para o algoritmo de busca gulosa
void mergeGreedy(std::vector<State*>& list, int begin, int mid, int end) {
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    std::vector<State*> left(n1);
    std::vector<State*> right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = list[begin + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = list[mid + 1 + j];
    }

    int i = 0;  
    int j = 0;  
    int k = begin;  

    while (i < n1 && j < n2) {
        if (left[i]->heuristic() <= right[j]->heuristic()) {
            list[k] = left[i];
            i++;
        } else {
            list[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        list[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        list[k] = right[j];
        j++;
        k++;
    }
}

void mergeSortGreedy(std::vector<State*>& list, int begin, int end) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;

        mergeSortGreedy(list, begin, mid);

        mergeSortGreedy(list, mid + 1, end);

        mergeGreedy(list, begin, mid, end);
    }
}

// Funções de Ordenação para o algoritmo de busca A*
void mergeAstar(std::vector<State*>& list, int begin, int mid, int end) {
    int n1 = mid - begin + 1;
    int n2 = end - mid;

    std::vector<State*> left(n1);
    std::vector<State*> right(n2);

    for (int i = 0; i < n1; i++) {
        left[i] = list[begin + i];
    }
    for (int j = 0; j < n2; j++) {
        right[j] = list[mid + 1 + j];
    }

    int i = 0;  
    int j = 0;  
    int k = begin;  

    while (i < n1 && j < n2) {
        if ((left[i]->heuristic() + left[i]->cost()) <= (right[j]->heuristic() + right[j]->cost())) {
            list[k] = left[i];
            i++;
        } else {
            list[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        list[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        list[k] = right[j];
        j++;
        k++;
    }
}

void mergeSortAstar(std::vector<State*>& list, int begin, int end) {
    if (begin < end) {
        int mid = begin + (end - begin) / 2;

        mergeSortAstar(list, begin, mid);

        mergeSortAstar(list, mid + 1, end);

        mergeAstar(list, begin, mid, end);
    }
}

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

std::vector<State*> State::getParents(){
    
    return this->parents;

}

void State::setLastParent(State* parent){

    this->parents.push_back(parent);

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

bool State::isPossible(){

    int initialStateInversions = 0;
    int finalStateInversions = 0;
    int size =  this->board->getSize();

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

std::vector<State*> State::generateChildStates() {
    int zeroX = this->board->getZeroPosition()[0];
    int zeroY = this->board->getZeroPosition()[1];

    std::vector<State*> childStates;

    for (const std::string& movement : movements) {
        State* childState = new State(this->board->getBoardCopy(), this->finalState, this->parents);
        childState->getParents().push_back(this);
        
        if (movement == "Up") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX - 1, zeroY);
        } else if (movement == "Down") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX + 1, zeroY);
        } else if (movement == "Left") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX, zeroY - 1);
        } else if (movement == "Right") {
            childState->getBoard()->swapPieces(zeroX, zeroY, zeroX, zeroY + 1);
        }
        
        childStates.push_back(childState);
    }

    return childStates;
}

bool State::backtracking(int& visitedNodes, int& expandedNodes){ // Busca backtracking -> gera apenas um filho por vez 
    expandedNodes++;

    if(this->isFinalState()) { //Verifica se o estado atual é o estado final
        cout << endl << "End of the search." << endl;
        cout << endl << "Movements: " << endl;
        if (!this->getParents().empty()) {
            for (State* parent : this->getParents()) {
                parent->getBoard()->printBoard();
                cout << endl;
            }
        }
        cout << endl << "Solution depth: " << getParents().size() << endl;
        cout << "Solution cost: " << visitedNodes << endl; // O custo da solução é o número de estados fechados visitados
        cout << "Expanded nodes: " << expandedNodes << endl;
        cout << "Visited nodes: " << visitedNodes << endl; // O número de nós visitados é igual ao número de estados fechados
        cout << "Average branching factor value: " << static_cast<double>(visitedNodes) / expandedNodes << endl;
        return true;
    }

    this->possibleMovements(); // Verifica os possíveis movimentos

    std::vector<State*> childStates = this->generateChildStates(); // Geração dos filhos

    visitedNodes = visitedNodes +  childStates.size();

    if(!this->getParents().empty()){
        for (State* parent : this->getParents()) { //Para cada filho gerado verifica se o mesmo não é pai do estado atual
            for(State* childState : childStates){
                if(childState->isEqualState(parent)){
                            vector<State*>::iterator new_end = std::remove(childStates.begin(), childStates.end(), childState);
                            childStates.erase(new_end, childStates.end());
                }
            }
        }
    }

    if (!childStates.empty()) {
        for (State* childState : childStates) { // Para cada filho gerado
                childState->setLastParent(this); // Atualiza a lista de pais
                if(childState->backtracking(visitedNodes,expandedNodes)) // Chama recursivamente o backtracking para o filho
                    return true;
        }
    }
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

void State::ordered(){ //Busca Ordenada -> seleciona sempre o de menor custo debtro do custo calculado
    std::vector<State*> openStates; //Vetor de estados abertos
    std::unordered_set<State*> closedStates; //Lista de estados fechados (todos os filhos foram gerados)
    int childState = 0;

    openStates.push_back(this); //Adiciona o estado inicial a lista de abertos

    while (!openStates.empty()) {

        mergeSortOrdered(openStates, 0, openStates.size()-1); //Ordenação da lista por custo 
        State* currentState = openStates.front(); //Primeiro estado da lista vira o estado atual (estado de menor custo)

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

        openStates.erase(openStates.begin());  //Estado removido da fila de estados abertos 
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
                    openStates.push_back(childState); // Adiciona o filho na fila
                }
            }
        }
    }


}

void State::greedy(){ //Busca Gulosa -> seleciona sempre o de menor custo dentro da heurística
    std::vector<State*> openStates; //Vetor de estados abertos
    std::unordered_set<State*> closedStates; //Lista de estados fechados (todos os filhos foram gerados)
    int childState = 0;

    openStates.push_back(this); //Adiciona o estado inicial a lista de abertos

    while (!openStates.empty()) {

        mergeSortGreedy(openStates, 0, openStates.size()-1); //Ordenação da lista pelo custo da heurística
        State* currentState = openStates.front(); //Primeiro estado da lista vira o estado atual (estado de menor custo da heurística)

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

        openStates.erase(openStates.begin());  //Estado removido da fila de estados abertos 
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
                    openStates.push_back(childState); // Adiciona o filho na fila
                }
            }
        }
    }



}

void State::aStar(){ //Busca A* -> seleciona sempre o de menor custo em relação ao custo + heurística 
    std::vector<State*> openStates; //Vetor de estados abertos
    std::unordered_set<State*> closedStates; //Lista de estados fechados (todos os filhos foram gerados)
    int childState = 0;

    openStates.push_back(this); //Adiciona o estado inicial a lista de abertos

    while (!openStates.empty()) {

        mergeSortAstar(openStates, 0, openStates.size()-1); //Ordenação da lista pelo custo da heurística + custo
        State* currentState = openStates.front(); //Primeiro estado da lista vira o estado atual (estado de menor custo da heurística+custo)

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

        openStates.erase(openStates.begin());  //Estado removido da fila de estados abertos 
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
                    openStates.push_back(childState); // Adiciona o filho na fila
                }
            }
        }
    }

}

bool State::auxIdaStar(int g, int& visitedNodes, int& expandedNodes, double& avgBranchingFactor, int threshold)
{
    int f = g + this->cost() + this->heuristic();  // Cálculo do valor f = g + h

    if (f > threshold) {
        return false;  // Limite excedido, não expande mais esse nó
    }

    if (this->isFinalState()) {
        cout << endl << "End of the search." << endl;
        cout << endl << "Movements: " << endl;
        if (!this->getParents().empty()) {
            for (State* parent : this->getParents()) {
                parent->getBoard()->printBoard();
                cout << endl;
            }
        }
        cout << endl << "Solution depth: " << getParents().size() << endl;
        cout << "Solution cost: " << visitedNodes << endl;
        cout << "Expanded nodes: " << expandedNodes << endl;
        cout << "Visited nodes: " << visitedNodes << endl;
        cout << "Average branching factor value: " << avgBranchingFactor << endl;
        return true;
    }

    this->possibleMovements();

    std::vector<State*> childStates = this->generateChildStates();

    expandedNodes += childStates.size();
    avgBranchingFactor = static_cast<double>(expandedNodes) / visitedNodes;

    for (State* childState : childStates) {
        childState->setLastParent(this);
        visitedNodes++;

        if (childState->auxIdaStar(g + 1, visitedNodes, expandedNodes, avgBranchingFactor, threshold)) {
            return true;
        }
    }

    return false;
}

void State::idaStar(){
    int visitedNodes = 0;
    int expandedNodes = 0;
    double avgBranchingFactor = 0.0;
    int threshold = this->cost() +  this->heuristic();

    while (true) {
        if (auxIdaStar(0, visitedNodes, expandedNodes, avgBranchingFactor, threshold)) {
            break;  // Solução encontrada
        }
        threshold = 50;  // Aumenta o limite de busca
    }
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