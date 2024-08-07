//
//  VirtualBoard.hpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 3/8/24.
//

#pragma once

#include "array"

#include "GLOBAL.h"
#include "LNotate.hpp"

/*
     * WARNING VirtualBoard is not intended for large history.
     * More than 50 moves (in history array) will make it break.
 */

class VirtualBoard {
public:
    
    // NOTE: (int) PieceType == (board array white pieces int number) - 1
    
    std::array<int, 64> boardarray{};
    std::array<LNotate, 50> history{}; // can only contain 50 moves.
    
    /* for boardarray:
     
     1 = white pawn
     2 = white knight
     3 = white bishop
     4 = white rook
     5 = white queen
     6 = whiteking
     -1 = black pawn
     -2 = black bishop
     -3 = black knight
      etc.
     
     */
    
    VirtualBoard() = default;
    
    void putPiece(int, PieceType, PieceColor);
    
    void pullPiece(int);
    
};
