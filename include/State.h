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

        State(Board *board, State *finaState, std::vector<State> parents);
        bool isFinalState();
        void possibleMovements();
        void createChildren();

};

#endif  // STATE_H