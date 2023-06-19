#ifndef PIECE_H
#define PIECE_H

using namespace std;

class Piece{

    private:

        int value;
        int xPiecePosition;
        int yPiecePosition;

    public:

        Piece(int value, int xPiecePosition, int yPiecePosition);

        void setValue(int value);
        int getValue();

        std::vector<int> getPosition();

};

#endif  // PIECE_H