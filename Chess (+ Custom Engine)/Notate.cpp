//
//  Notate.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 26/3/23.
//

#include "Notate.hpp"
#include <iostream>

Notate::Notate(TypeNoT a, Square* b, Square* c, AddNoT d) :

    NoT{a} , From{b}, To{c}, ADD(d)

{
        if (c && c->HoldingPiece) piece = new Piece{*c->HoldingPiece};
            // sets piece variable to new copy of the "to" square -> HoldingPiece
        
        /*if (
             a!=REMOVE && piece->type == PAWN &&
            
            (
             
            (b->BoardPosition_notation.numberCordinate +2 == c->BoardPosition_notation.numberCordinate) ||
            (b->BoardPosition_notation.numberCordinate -2 == c->BoardPosition_notation.numberCordinate)
             
             )
            
            )
        
        {
            
            ADD = DOUBLEFORWARD;
            
        }*/ 
        
}

void Notate::print(string e) {
    cout << sprint() << e;
}

string Notate::sprint() {
    // this gets called every loop
    
    //### if TypeNoT is create "from" square is nullptr "to" square is not
    //### if TypeNoT is remove "from" square is not nullptr "to" square is nullptr
    
    string r{};
    
    // note r is
    // if NoT is create then +(piece type)("from" square position) ### PIECE TYPE
    // if NoT is remove then -("from" square position)   ### NO PIECE TYPE
    // piece is nullptr when NoT is remove
    
    if (ADD==CASTLE) {
        if (To->BoardPosition_notation.characterCordinate == 'g') r+= "O-O";
            // kingside castling (O-O) if it goes right
        else r+= "O-O-O";
            // else queenside castling (O-O-O)
        return r;
    }
    
    if (NoT==REMOVE) r += "-";
    if (NoT == CREATE) r += "+";
    
    if (NoT != REMOVE) {
    
        if(piece->type == KNIGHT) r+='n';
        if(piece->type==BISHOP)r+='b';
        if(piece->type==ROOK)r+='r';
        if(piece->type==QUEEN)r+='q';
        if(piece->type==KING)r+='k';
        
    }
        
    
    
    if (! (NoT==CREATE) && From ) r+=From->BoardPosition_notation.PrintOutString();
    // puts the "from" square notation
    // when TypeNoT is  remove it gets position from this ^^^
    
    if (NoT==REMOVE) return r;
    
    if(NoT==TAKE)r+='x';
    
    r+=To->BoardPosition_notation.PrintOutString();
    // puts the "to" square notation
    // ^^ when TypeNoT is create it gets position from this
    
    return r;
}
