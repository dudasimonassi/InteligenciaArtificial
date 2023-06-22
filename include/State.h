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
        std::vector<string> path;
        int depth = 0;
        double branchingFactorSum = 0; 
        int nodeCount = 1; 
        int expandedCount = 0; 
        int visitedCount = 0; 

    public:

        State(Board *board, State *finalState, std::vector<State*> parents);
        State(Board *board);
        
        Board* getBoard();
        State* getFinalState();
        int getDepth();
        int getSize();
        std::vector<State*> getParents();
        std::vector<string> getPath();
        double getBranchingFactorSum();
        int getNodeCount();
        int getExpandedCount();
        int getVisitedCount();

        void setBranchingFactorSum(double branchingFactorSumIncrement);
        void setNodeCount(int nodeCountIncrement);
        void setExpandedCount(int expandedCountIncrement);
        void setVisitedCount(int visitedCountIncremen);
        void setLastParent(State* parent);

        bool isFinalState();
        bool isEqualState(State * state);
        bool isPossible();

        void possibleMovements();

        void backtracking(State * initialState);
        void bfs();
        void dfs();
        void ordered();
        void greedy();
        void aStar();
        void idaStar();

};

#endif  // STATE_H