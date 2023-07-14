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

std::vector<int> Board::getZeroPosition(){

    for(int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            if(pieces[i][j]->getValue() == 0){

                return pieces[i][j]->getPosition();

            }
        }
    }

}

std::vector<int> Board::getPosition(int value){

    for(int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            if(pieces[i][j]->getValue() == value){

                return pieces[i][j]->getPosition();

            }
        }
    }

}

Board* Board::getBoardCopy() {
    Board* boardCopy = new Board(this->size);

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Piece* piece = this->pieces[i][j];
            Piece* pieceCopy = new Piece(piece->getValue(), piece->getPosition()[0], piece->getPosition()[1]);
            boardCopy->setPiece(pieceCopy, i, j);
        }
    }

    return boardCopy;
}

void Board::setPiece(Piece *piece,int positionX, int positionY){

    pieces[positionX][positionY] = piece;

}

void Board::printBoard(){

 for(int i=0; i<size; i++){

        for(int j=0; j<size; j++){

            cout << this->getPiece(i,j)->getValue() << "  "; 
        
        }

        cout << endl;

    }

}

void Board::swapPieces(int x1, int y1, int x2, int y2) {
    Piece* piece1 = this->pieces[x1][y1];
    Piece* piece2 = this->pieces[x2][y2];

    // Atualiza as posições das peças
    piece1->xPiecePosition = x2;
    piece1->yPiecePosition = y2;
    piece2->xPiecePosition = x1;
    piece2->yPiecePosition = y1;

    // Realiza a troca das peças no tabuleiro
    this->pieces[x1][y1] = piece2;
    this->pieces[x2][y2] = piece1;
}
