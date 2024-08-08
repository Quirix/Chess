//
//  VirtualBoard.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 3/8/24.
//

#include "VirtualBoard.hpp"

#include <iostream>

#include "FUNCTIONS.h"

void VirtualBoard::translateToVirtual(const vector<Piece*>& PiecesVector, const vector<Notate*>& HistoryVector)
{
    for (auto* e : PiecesVector) {
        if (e && e->OnSquare) {
            
            boardarray[e->OnSquare->BoardPosition_num-1] = normalToInf(e->type, e->piececolor);
        }
    }
    
    if (HistoryVector.size() > 20) {
        for (int i = 0; i < 20; i++) {
            Notate* n = (*(HistoryVector.end()-i));
            if ( (n->NoT != CREATE) && (n->NoT != REMOVE)) {
                history[countHistory].To = n->To->BoardPosition_num;
                history[countHistory].From = n->From->BoardPosition_num;
                history[countHistory].special = n->ADD;
                history[countHistory].inf = normalToInf(n->piece->type, n->piece->piececolor);
                countHistory++;
            }
        }
        
        return;
    }
    
    for (auto* e : HistoryVector) {
        if ( (e->NoT != CREATE) && (e->NoT != REMOVE)) {
            history[countHistory].To = e->To->BoardPosition_num;
            history[countHistory].From = e->From->BoardPosition_num;
            history[countHistory].special = e->ADD;
            history[countHistory].inf = normalToInf(e->piece->type, e->piece->piececolor);
            countHistory++;
        }
    }
    
}

void VirtualBoard::putPiece(int index, PieceType type, PieceColor color) {
    // index should be from 1-64
    
    boardarray[index-1] = normalToInf(type, color);
    // turns piecetype and piececolor to integer to represent that piece for the array.
    
    // this doesn't append anything to history.
}

void VirtualBoard::pullPiece(int index) {
    // index should be from 1-64
    
    boardarray[index-1] = 0;
    
    // this doesn't append anything to history.
}
