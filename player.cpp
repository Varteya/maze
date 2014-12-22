#include "Player.h"

player::player()
{

}

void player::initialize_coordinates (std::istream & in)
{
    int x;
    int y;
    in >> x;
    in >> y;
    coordinate = std::pair<int,int>(x, y);
}

