#include <iostream>
#include "Field.h"


Field::Field() {
}

void Field::readFieldFromFile(std::istream &in) {
    numberOfWalls = 0;
    in >> size;
    places.resize(size * size);

    for (int j = 0; j < size; ++j) {
        for (int i = 0; i < size; ++i) {
            char now;
            in >> now;
            switch (now) {
                case 'E':
                    addValue(i, j, EMPTY);
                    break;
                case 'W':
                    addValue(i, j, WALL);
                    numberOfWalls = numberOfWalls + 1;
                    break;
                case 'F':
                    addValue(i, j, PORTAL);
                    break;
                default:
                    throw "Bad char";
            }
        }
    }
}


void Field::addValue(int x, int y, Field::typeOfPlace type) {
    int coordinate = (size - 1 - y) * size + x;
    Field::places[coordinate] = type;
}

Field::typeOfPlace Field::readValue(int x, int y) {
    int coordinate = y * size + x;
    return places[coordinate];
}

