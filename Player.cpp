#include "Player.h"


void Player::move(Player::type_of_move typeOfMove) {
    Field::type_of_place typeOfField;
    switch (typeOfMove) {
        case LEFT: typeOfField = _field->read_value(_x -1, _y); break;
        case RIGHT: typeOfField = _field->read_value(_x +1, _y); break;
        case DOWN: typeOfField = _field->read_value(_x, _y -1); break;
        case UP: typeOfField = _field->read_value(_x, _y +1); break;
    }

    if(typeOfField == Field::PORTAL){
        exit(0);
    } else if(typeOfField == Field::EMPTY){
        switch (typeOfMove) {
            case LEFT: --_x; break;
            case RIGHT: ++_x; break;
            case DOWN: --_y; break;
            case UP: ++_y; break;
        }
    }
}

Player::Player(Field *field, int x, int y) :
        _field(field),
        _x(x),
        _y(y)
        {}

