#ifndef STATE_H
#define STATE_H

#include <iostream>
#include <vector>
#include <string>
#include "Piece.h"
#include "Board.h"

using namespace std;

class State{

    private:

        Board *board;
        State *finalState;
        std::vector<std::string> movements{"Up", "Down", "Right", "Left"};
        std::vector<State> parents;

    public:

        State(Board *board, State *finalState, std::vector<State> parents);
        Board* getBoard();
        State* getFinalState();
        int getSize();
        bool isFinalState();
        void possibleMovements();
        bool isPossible();

};

#endif  // STATE_H