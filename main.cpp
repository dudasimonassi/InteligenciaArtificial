#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <chrono>
#include <stack>
#include <list>
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

    std::vector<State*> parents;

    State *finalState = new State(finalBoard);

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

            auto start = std::chrono::high_resolution_clock::now();

            switch (option) {
                case 0:

                    cout << "Exiting the program." << endl;
                    break;

                case 1:{
                    int visitedNodes = 0;
                    int expandedNodes = 0;   
                    
                    cout << "You choose Backtracking." << endl;

                    initialState->backtracking(visitedNodes, expandedNodes);

                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl <<"Search processing time: " << duration << " microseconds" << endl;

                    break;
                }
                case 2:{
                    cout << endl << "You choose Breadth-First Search." << endl;
                    initialState->bfs();

                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl << "Search processing time: " << duration << " microseconds" << endl;
                    break;
                }
                case 3:{
                    cout << endl << "You choose Depth-First Search." << endl;
                    initialState->dfs();

                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl << "Search processing time: " << duration << " microseconds" << endl;
                    break;
                }
                case 4:{
                    cout << endl << "You choose Ordered Search." << endl;
                    initialState->ordered();

                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl << "Search processing time: " << duration << " microseconds" << endl;
                    break;
                }
                case 5:{
                    cout << endl << "You choose Greedy Search." << endl;
                    initialState->greedy();

                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl << "Search processing time: " << duration << " microseconds" << endl;
                    break;
                }
                case 6:{
                    cout << endl << "You choose A* Search." << endl;
                    initialState->aStar();

                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl << "Search processing time: " << duration << " microseconds" << endl;
                    break;
                }
                case 7:{
                    cout << endl << "You chose IDA* Search." << endl;
                
                    initialState->idaStar();
                    
                    auto end = std::chrono::high_resolution_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

                    cout << endl << "Search processing time: " << duration << " microseconds" << endl;
                    break;
                }
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

