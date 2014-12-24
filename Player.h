#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <iostream>
#include "Field.h"

class Player {
public:
    enum type_of_move
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
    void move(type_of_move typeOfMove);
private:
    Field * _field;
    int _x;
    int _y;
};

#endif // PLAYER_H
