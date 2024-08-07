//
//  VirtualBoard.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 3/8/24.
//

#include "VirtualBoard.hpp"

#include <iostream>

void VirtualBoard::putPiece(int index, PieceType type, PieceColor color) {
    // index should be from 1-64
    
    boardarray[index-1] = (((int) type) + 1) * (int) color;
    // turns piecetype and piececolor to integer to represent that piece for the array.
}

void VirtualBoard::pullPiece(int index) {
    // index should be from 1-64
    
    boardarray[index-1] = 0;
    
}
