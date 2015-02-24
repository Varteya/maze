#ifndef FIELD_H
#define FIELD_H

#include <utility>
#include <vector>


class Field
{
public:
    Field();

    void readFieldFromFile(std::istream &);
    //Reading text map from file and initialize filed

    enum typeOfPlace
    {
        EMPTY,
        WALL,
        PORTAL  //Exit
    };

    int size;

    std::vector<typeOfPlace> places;
    int numberOfWalls;

    void addValue(int, int, typeOfPlace);
    //inintialize element of the field with coordinates by typeOfPlace

    typeOfPlace readValue(int, int);
    //read typeOfPlace on the field on coordinates

};


#endif // FIELD_H
