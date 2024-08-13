#pragma once

enum Check {
    NOCHECK = 0,
    BLACKTOWHITE = 1,
    WHITETOBLACK = -1,
    BOTHCHECK = 2
};

 extern int WindowWidth;
 extern int WindowHeight;

 extern float squareWidth;
 extern float squareHeight;

extern int castleState;

/* ^^^ castleState doc
 (only if space is given and square is not attacked and +)
 (so not to track the whole history. Changes when king moves or rook)
 2: king able to castle both ways
 1: king able to castle kingside
 0: king able to castle queenside
 -1: king is not able to castle
*/


extern bool DissallowLegalMoves;
extern bool TakeTurns;
extern bool CanCreate;
extern bool Serious; // non-debug

extern Check Checking;

enum PieceType {
   PAWN = 0,
   KNIGHT = 1,
   BISHOP = 2,
   ROOK = 3,
   QUEEN = 4,
   KING = 5
};

enum PieceColor {
   WHITE= 1,
   BLACK= -1
};

enum AddNoT {
    CLASSIC,
    PESSANT,
    CASTLE,
    DOUBLEFORWARD // pawns
};

enum TypeNoT {
    CREATE,
    REMOVE, // manual remove by destroy
    MOVE, // basic
    TAKE,
    CHECK,
    MATE,
    DRAW // symbol - ?
    
};
