//
//  Move.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 26/3/23.
//

#include "Move.hpp"

Move::Move(TypeNoT a, AddNoT b, Square* c)

: type{a}, special{b}, square(c)

{
    
}

Move::Move(Square* a) : square{a}, type{MOVE}, special(CLASSIC) {
    
}

Move::Move(Square* a, TypeNoT b, AddNoT c  )

: square{a}, type{b}, special{c}

{
    
}
