#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <iostream>
#include "Field.h"

class Player {
public:
    enum typeOfMove
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Player(Field * field, int x, int y);

    int getXCoord(){
        return _x;
    }

    int getYCoord(){
        return _y;
    }

    void move(typeOfMove typeOfMove);
    //change players coordinates

    bool isEscaped();
    //check if player won
private:
    Field * _field;
    int _x;
    int _y;
    bool escaped;
};

#endif // PLAYER_H
