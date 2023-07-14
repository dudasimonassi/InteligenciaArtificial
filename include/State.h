#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include <chrono>
#include "Piece.h"
#include "Board.h"

using namespace std;

class State{

    private:

        Board *board;
        State *finalState;
        std::vector<std::string> movements{"Up", "Down", "Right", "Left"};
        std::vector<State*> parents;
        string movement;

    public:

        State(Board *board, State *finalState, std::vector<State*> parents);
        State(Board *board);
        
        Board* getBoard();
        State* getFinalState();
        int getSize();
        std::vector<State*> getParents();
        string getMovement();

        void setLastParent(State* parent);
        void setMovement(string movement);

        bool isFinalState();
        bool isEqualState(State * state);
        bool isPossible();
        vector<State*> generateChildStates();
        void possibleMovements();

        void backtracking();
        void bfs();
        void dfs();
        void ordered();
        void greedy();
        void aStar();
        void idaStar();

        int cost();
        int heuristic();
};

#endif  // STATE_H