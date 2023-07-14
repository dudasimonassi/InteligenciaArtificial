#ifndef PIECE_H
#define PIECE_H

using namespace std;

class Piece{

    private:

        int value;


    public:

        Piece(int value, int xPiecePosition, int yPiecePosition);

        int xPiecePosition;
        int yPiecePosition;

        int getValue();
        void setValue(int value);
        
        std::vector<int> getPosition();

};

#endif  // PIECE_H