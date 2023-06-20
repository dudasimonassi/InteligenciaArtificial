#include <iostream>
#include <vector>
#include "../include/Piece.h"
#include "../include/Board.h"

using namespace std;

Board::Board(int size){

    this->size = size;

    pieces.resize(size, std::vector<Piece*>(size)); 

}

int Board::getSize(){

    return this->size;

}


Piece* Board::getPiece(int positionX, int positionY){

    return pieces[positionX][positionY];

}

void Board::setPiece(Piece *piece,int positionX, int positionY){

    pieces[positionX][positionY] = piece;

}

std::vector<int> Board::getZeroPosition(){

    for(int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            if(pieces[i][j]->getValue() == 0){

                return pieces[i][j]->getPosition();

            }
        }
    }

}

void Board::printBoard(){

 for(int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            cout << this->getPiece(i,j)->getValue() << "  "; 
        
        }

        cout << endl;

    }

}