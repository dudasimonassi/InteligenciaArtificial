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

    public:

        State(Board *board, State *finalState, std::vector<State*> parents);
        State(Board *board);
        
        Board* getBoard();
        State* getFinalState();
        std::vector<State*> getParents();

        void setLastParent(State* parent);

        bool isFinalState();
        bool isEqualState(State * state);
        bool isPossible();
        void possibleMovements();
        vector<State*> generateChildStates();

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