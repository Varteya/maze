#include "Player.h"


void Player::move(Player::typeOfMove typeOfMove) {
    Field::typeOfPlace typeOfField;
    switch (typeOfMove) {
        case LEFT: typeOfField = _field->readValue(_x - 1, _y); break;
        case RIGHT: typeOfField = _field->readValue(_x + 1, _y); break;
        case DOWN: typeOfField = _field->readValue(_x, _y - 1); break;
        case UP: typeOfField = _field->readValue(_x, _y + 1); break;
    }

    if(typeOfField == Field::PORTAL){
        escaped = true;
    } else if(typeOfField == Field::EMPTY){
        switch (typeOfMove) {
            case LEFT: --_x; break;
            case RIGHT: ++_x; break;
            case DOWN: --_y; break;
            case UP: ++_y; break;
        }
    }
}

bool Player::isEscaped() {
    return escaped;
}

Player::Player(Field *field, int x, int y) :
        _field(field),
        _x(x),
        _y(y),
        escaped(false)
        {}

