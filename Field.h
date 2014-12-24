#ifndef FIELD_H
#define FIELD_H

#include <utility>
#include <vector>


class Field
{
public:
    Field();
//    ~Field();
    void read_field_from_file(std::istream &);

    enum type_of_place
    {
        EMPTY,
        WALL,
        PORTAL
    };

    int size;

 //   int places_height;
 //   int places_width;
    std::vector< type_of_place > places;
    int number_of_walls;

    void add_value(int, int, type_of_place);
    type_of_place read_value(int, int);


};


#endif // FIELD_H
