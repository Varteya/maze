#include <iostream>
#include "Field.h"


Field::Field() {
}

void Field::read_field_from_file(std::istream &in) {
    number_of_walls = 0;
    in >> size;
    places.resize(size * size);

    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            char now;
            in >> now;
            switch (now) {
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


void Field::add_value(int x, int y, Field::type_of_place type) {
    int coordinate = (size - 1 - y) * size + x;
    Field::places[coordinate] = type;
}

Field::type_of_place Field::read_value(int x, int y) {
    int coordinate = y * size + x;
    return places[coordinate];
}
