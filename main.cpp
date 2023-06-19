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

using namespace std;

Board * readFile(ifstream& input_file){

    int size;
    int pieceValue;

    input_file >> size;

    Board* board = new Board(size);

    for(int i = 0; i<size; i++){

        for(int j = 0; j<size; j++){

            input_file >> pieceValue;
            Piece piece = Piece(pieceValue, i, j);
            board->setPiece(piece, i, j);

        }

    }

    


    return board;
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

    Board *board;

    if(input_file.is_open())
        board = readFile(input_file);
        
    else 
        cout << "\nNao foi possivel abrir o arquivo  " << argv[1] << "\n";
        

    input_file.close();

    output_file.close();

    return 0;
}

