#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Piece.h"

using namespace std;

class Board{

    private:

        int size;
        std::vector<std::vector<Piece*>> pieces;

    public:

        Board(int size);

        int getSize();
        Piece* getPiece(int positionX, int positionY);
        std::vector<int> getZeroPosition();
        std::vector<int> getPosition(int value);
        Board* getBoardCopy();

        void setPiece(Piece *piece, int positionX, int positionY);

        void printBoard();
        void swapPieces(int x1, int y1, int x2, int y2);

};

#endif  // BOARD_H