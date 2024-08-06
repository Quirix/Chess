//
//  LNotate.hpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 6/8/24.
//

#pragma once

#include <array>
#include "GLOBAL.h"

// LNotate = Light Notate
class LNotate {
public:
    //* TypeNot (CREATE, REMOVE, DRAW, WIN, TAKE ..) is not included.
    //* special is AddNot basically.
    
    /* special = 
     CLASSIC = 0
     PESSANT = 1
     CASTLE = 2
     DOUBLEFORWARD = 3
     */
    
    AddNoT special;
    int inf; // int form
    
    int From; // on board index
    int To; // on board index
    
    LNotate(AddNoT, int, int, int);
    
    void print();
    std::array<int, 4> sprint();
    
    bool operator==(const LNotate&);
};
