#ifndef PLAYER_H
#define PLAYER_H

#include <algorithm>
#include <iostream>
#include "field.h"

class player {

    enum type_of_move
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

public:
    player();
    void initialize_coordinates (std::istream &);

private:
    void move();


    std::pair<int, int> coordinate;

};

#endif // PLAYER_H
