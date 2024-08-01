#pragma once

#include "Notate.hpp"
#include "GLOBAL.h"
#include "Square.h"

class Square;

class Move {
public:
    
    TypeNoT type;
    AddNoT special;
    Square* square;
    
    Move() = default;
    Move(TypeNoT a, AddNoT b, Square* square);
    Move(Square* square, TypeNoT, AddNoT c = AddNoT{} );
    Move(Square* square);
    
};
