#include "../include/Piece.h"
#include <vector>

using namespace std;

Piece::Piece(int value, int xPiecePosition, int yPiecePosition){

    this->value = value;

    this->xPiecePosition = xPiecePosition;

    this->yPiecePosition = yPiecePosition;

}

int Piece::getValue(){

    return this->value;

}

void Piece::setValue(int value){

    this->value = value;

}

std::vector<int> Piece::getPosition() {

    return {this->xPiecePosition, this->yPiecePosition};

}