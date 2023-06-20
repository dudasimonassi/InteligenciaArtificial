#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <chrono>
#include <ctime>
#include "include/Board.h"
#include "include/Piece.h"
#include "include/State.h"
#include "src/Board.cpp"
#include "src/Piece.cpp"

using namespace std;

State * readFile(ifstream& input_file){

    int size;
    int pieceValue;

    input_file >> size;

    Board* board = new Board(size);

    for(int i = 0; i<size; i++){

        for(int j = 0; j<size; j++){

            input_file >> pieceValue;
            Piece *piece = new Piece(pieceValue, i, j);
            board->setPiece(piece, i, j);

        }

    }

    Board *finalBoard = new Board(size);

    for(int i = 0; i<size; i++){

        for(int j = 0; j<size; j++){

            input_file >> pieceValue;
            Piece *piece = new Piece(pieceValue, i, j);
            finalBoard->setPiece(piece, i, j);

        }

    }

    std::vector<State> parents;

    State *finalState = new State(finalBoard, finalState, parents);

    State *initialState = new State(board, finalState, parents);

    return initialState;
}

int main (int argc, char const *argv[]){

    if (argc != 3) { 

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file>" << endl;

        return 1;

    }
    
    string program_name(argv[0]);
    string input_file_name = argv[1];

    ifstream input_file;
    ofstream output_file;
    string output_file_name = argv[2];

    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    State *initialState;

    if(input_file.is_open()){
        initialState = readFile(input_file);
        initialState->getBoard()->printBoard();
    }
      
    else 
        cout << "\nNao foi possivel abrir o arquivo  " << argv[1] << "\n";
        

    input_file.close();

    output_file.close();

    return 0;
}

