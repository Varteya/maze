#include <iostream>
#include <string>
#include "field.h"



field::field()
{
}

void field::read_field_from_file(std::istream & in)
{
    number_of_walls = 0;
    in >> size;
    places.resize(size * size);
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            char now;
            in >> now;
            switch(now){
            case 'E':
                add_value(i, j, EMPTY);
                break;
            case 'W':
                add_value(i, j, WALL);
                number_of_walls = number_of_walls + 1;
                break;
            case 'F':
                add_value(i, j, PORTAL);
                break;
            default:
                throw "Bad char";
            }
        }
    }
}


void field::add_value(int x, int y, field::type_of_place type) {
    int coordinate = y * size + x;
    field::places[coordinate] = type;
}

field::type_of_place field::read_value(int x, int y) {
    int coordinate = y * size + x;
    return places[coordinate];
}
