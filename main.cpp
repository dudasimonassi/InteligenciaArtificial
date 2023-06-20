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
#include "src/State.cpp"

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

void mainMenu(State *initialState){

        int option = 1;

        while(option != 0){

            cout << "\n";
            cout << " -------------------------------------------------------" << endl;
            cout << "|                         MENU                          |" << endl;
            cout << " ------------------------------------------------------- " << endl;
            cout << "|                                                       |" << endl;
            cout << "| 1. Backtracking                                       |" << endl;
            cout << "| 2. Breadth-First Search                               |" << endl;
            cout << "| 3. Depth-First Search                                 |" << endl;
            cout << "| 4. Ordered Search                                     |" << endl;
            cout << "| 5. Greedy Search                                      |" << endl;
            cout << "| 6. A* Search                                          |" << endl;
            cout << "| 7. IDA* Search                                        |" << endl;
            cout << "|                                                       |" << endl;
            cout << "| 0. Exit                                               |" << endl;
            cout << "|                                                       |" << endl;
            cout << " -------------------------------------------------------" << endl;
            cout << "Enter the desired option: ";

            cin >> option;

            switch (option) {
                case 0:
                    cout << "Exiting the program." << endl;
                    break;
                case 1:
                    cout << "You chose Backtracking." << endl;
                    // Call the corresponding Backtracking function here
                    break;
                case 2:
                    cout << "You chose Breadth-First Search." << endl;
                    // Call the corresponding Breadth-First Search function here
                    break;
                case 3:
                    cout << "You chose Depth-First Search." << endl;
                    // Call the corresponding Depth-First Search function here
                    break;
                case 4:
                    cout << "You chose Ordered Search." << endl;
                    // Call the corresponding Ordered Search function here
                    break;
                case 5:
                    cout << "You chose Greedy Search." << endl;
                    // Call the corresponding Greedy Search function here
                    break;
                case 6:
                    cout << "You chose A* Search." << endl;
                    // Call the corresponding A* Search function here
                    break;
                case 7:
                    cout << "You chose IDA* Search." << endl;
                    // Call the corresponding IDA* Search function here
                    break;
                default:
                    cout << "Invalid option. Please try again." << endl;
                    break;
            }
        }

}

int main (int argc, char const *argv[]){

    if (argc != 2) { 

        cout << "ERROR: Expecting: ./<program_name> <input_file> " << endl;

        return 1;

    }
    
    string program_name(argv[0]);
    string input_file_name = argv[1];

    ifstream input_file;

    input_file.open(argv[1], ios::in);

    State *initialState;

    if(input_file.is_open()){

        initialState = readFile(input_file);
        if(initialState->isPossible() == true){
            mainMenu(initialState);
        }
        else
            cout << "ERROR: Unable to resolve the game.";

    }
      
    else 
        cout << "\nERROR: could not open the file " << argv[1] << "\n";
        

    input_file.close();

    return 0;
}

