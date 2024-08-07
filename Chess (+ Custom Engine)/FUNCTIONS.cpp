#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "GLOBAL.h"
#include "BoardPosition.h"
#include "Piece.h"
#include "Square.h"
#include "FUNCTIONS.h"
#include "Notate.hpp"
#include "LNotate.hpp"

#define makro window, BoardVector, PiecesVector, History

using namespace std;
using namespace sf;

RenderWindow* window;
vector<Piece*>* PiecesVector;
vector<Square*>* BoardVector;
vector<Notate*>* History;

void AssignStuff(RenderWindow* w, vector<Square*>* bv, vector<Piece*>* pv, vector<Notate*>* hs) {
    window = w;
    PiecesVector = pv;
    BoardVector = bv;
    History = hs;
}

BoardPositionNotation NumberToNotation(int number) {
   BoardPositionNotation a;
   
   int b = 0;
   int old = 1;
   
   for (int index = 1; index <= 8; index++) {
       if (number >= old && number <= (old-1)+8) {
           
           
           a.numberCordinate = 8 - (index-1);
           b = index;
           break;
       }
       
       old += 8;
   }
   
   a.characterCordinate = (char) ( (( number - 8* (b-1) )+96) );
   
   
   return a;
   
}

void EmptyFunction() {}

bool isMouseDragging() {
    
    
    static bool is_clicking = false;
    static Vector2i positionWhenClicked{};
    
    if (Mouse::isButtonPressed(Mouse::Left)) {
        
        if (is_clicking == false) {
            is_clicking = true;
            positionWhenClicked = Mouse::getPosition(*window);
            return false;
        }
        
        if (is_clicking == true && positionWhenClicked != Mouse::getPosition(*window) ) {
            return true;
        }
        
    }
    
    else {
        is_clicking = false;
    }
    
    return false;
}

bool IsMouseInRec(RectangleShape* rec) {
    Vector2i mousepos = Mouse::getPosition(*window);
    
    Vector2f position = rec->getPosition();
    Vector2f scale = rec->getSize();
    
    if ( (((float)mousepos.x) >= position.x) && (((float)mousepos.x) <= (position.x + scale.x))){
        
        if ( (((float) mousepos.y) >= (position.y)) && (((float)mousepos.y) <= (position.y + scale.y)) ) {
            return true;
        }
    }
    
    return false;
}

bool IsMousePressed() { // better name: mouse click ended
    static bool IsMouseclicked = false;
    
    if (Mouse::isButtonPressed(Mouse::Left)) {
        
        IsMouseclicked = true;
        
    }
    
    else {
        if (IsMouseclicked == true) {
            IsMouseclicked = false;
            return true;
        }
    }
    
    // when a click starts ismouseclicked is set to true and returns false
    // when a click ends, or when mouse is not pressed and ismouseclicked is set to true
        // then return true
    
    // long story short when a click ends, it returns true.
    
    return false;
}

int NotationToNumber(char CharacterCordiante, int NumberCordiante) {
    int x = 0;

  
    switch (NumberCordiante){
        case 8: x=0; break;
        case 7: x=8; break;
        case 6: x=8*2; break;
        case 5: x=8*3; break;
        case 4: x=8*4; break;
        case 3: x=8*5; break;
        case 2: x=8*6; break;
        case 1: x=8*7; break;
    }; // im sorry
    
    cout << (int) CharacterCordiante << '\n';
    x += ((int)CharacterCordiante) - 96;
    
    return x;
    
}

//* makes changes to global variables such as boardvector and or uses them.
void SetUpBoardVector() {
    
    int breaks = 0;
    
    Color Even_Odd = Color(0xeeeed2ff);
    Color Odd_Odd =  Color(0x779656ff);
    Color Even_Even = Color(0x779656ff);
    Color Odd_Even = Color(0xeeeed2ff);
    
    squareWidth = WindowWidth/8;
    squareHeight = WindowHeight/8;
    
    float position_x = -squareWidth;
    
    // if square is odd, square is (odd)), else square is (even))
    
    for (int index = 1; index <= 64; index++) {
        
        position_x += squareWidth;
        
        Square* square = new Square{makro};
        square->rec = new RectangleShape{Vector2f(squareWidth, squareHeight)} ;
        square->rec->setPosition(position_x, squareHeight * breaks);
        
        if (index % 2 == 0){ // even
            if (breaks % 2 == 0) square->rec->setFillColor(Even_Even);
            else square->rec->setFillColor(Even_Odd);
        }
            
            
        else {
            if (breaks % 2 == 0) square->rec->setFillColor(Odd_Even);
            else square->rec->setFillColor(Odd_Odd);
        }
        
        if ( ((float) index) / 8 == index / 8) {
            position_x = -squareWidth;
            breaks++;
            cout << index;
        }
            
        square->SetDefaultColor();
        square->SetBoardPosition(index);
        
        BoardVector->push_back(square);
        
        
    }
    
}

// the function below is responsible for detecting the mouse press and creating a piece.
void CheckMouse() {
    
    if (IsMousePressed()) {
        //cout << "Mouse Pressed\n";
            
        Square* element = SquareTouchingMouse();
        
        if (element) {
            //element->rec->setFillColor(Color::Red);
            element->BoardPosition_notation.PrintOut();
            Piece* e = new Piece{makro};
            
            Move move = {e->OnSquare};
            
            move.type = CREATE;
            
            e->MoveTo(move);
            PiecesVector->push_back(e);
        }
    }
}

Square* SquareTouchingMouse() {
    
    for (auto* element : *BoardVector) {
        if (IsMouseInRec(element->rec)) {
            return element;
        }
    }
    
    return nullptr;
}

bool CanTake(Piece* attacker,Piece* piece2) { // WARNING: NOT CONSIDERING: PINS, IN CHECK, ...
    if (!attacker || !piece2) return false;
    if (attacker->piececolor != piece2->piececolor) return true;
    return false;
}
// bx=boardindex
bool CanTake(int bx1, int inf1, int bx2, int inf2 ) { // WARNING: NOT CONSIDERING: PINS, IN CHECK, ...
    if (getColorInf(inf1) != getColorInf(inf2)) return true;
    return false;
}

//* makes changes to global variables such as boardvector and or uses them.
Square* wcCordinateToSquare(BoardPositionNotation n) { // wc standing for with check
    for (auto* v : *BoardVector) {
        if (v->BoardPosition_notation.PrintOutString() == n.PrintOutString()) return v;
    }
    
    cout << "oh no\n";
    cout << "error with cordinatetosquare function, boardpositionnotation = " << n.PrintOutString() << '\n';
    
    return nullptr;
}

Square* CordinateToSquare(BoardPositionNotation n) {
    
    for (auto* v : *BoardVector) {
        if (v->BoardPosition_notation.PrintOutString() == n.PrintOutString()) return v;
    }

    return nullptr;
}

Square* CordinateToSquare(char a, int b) {
    
    BoardPositionNotation n = BoardPositionNotation{a,b};
    
    for (auto* v : *BoardVector) {
        if (v->BoardPosition_notation.PrintOutString() == n.PrintOutString()) return v;
    }

    return nullptr;
}


Square* PL(BoardPositionNotation pos, int a, int b) {
    return CordinateToSquare( BoardPositionNotation( (char) (pos.characterCordinate+a), pos.numberCordinate+b));
}

int PL(int boardIndex, int a, int b) {
    std::cout << a << '\n';
    return 0;
}

//* makes changes to global variables such as boardvector and or uses them.
bool canTakeBlackKingAll(){
    for (auto* e : *PiecesVector)
    {
        if (e->piececolor == WHITE && e->CanTakeOppositeKing()) return true;
    }
    
    return false;
}
//* makes changes to global variables such as boardvector and or uses them.
bool canTakeWhiteKingAll(){
    for (auto* e : *PiecesVector)
    {
        if (e->piececolor == BLACK && e->CanTakeOppositeKing()) return true;
    }
    
    return false;
}

//* makes changes to global variables such as boardvector and or uses them.
void putPiecesInBoard()
{
    for (int i = 0 ; i < 8; i++) {
        PiecesVector->push_back(new Piece{PAWN, WHITE, PL( {'a',2}, i, 0 ) , makro} );
    }
    
    for (int i = 0 ; i < 8; i++) {
        PiecesVector->push_back(new Piece{PAWN, BLACK, PL( {'a',7}, i, 0 ) , makro} );
    }
    
    for (int i = 1 ; i >= -1; i -= 2 ) {
        
        PieceColor clr = (PieceColor) i;
        
        int pos = (clr==WHITE) ? 1 : 8;
        
        PiecesVector->push_back(new Piece{ROOK, clr, CordinateToSquare('a', pos),  makro} );
        PiecesVector->push_back(new Piece{KNIGHT, clr, CordinateToSquare('b', pos), makro} );
        PiecesVector->push_back(new Piece{BISHOP, clr, CordinateToSquare('c', pos), makro} );
        PiecesVector->push_back(new Piece{QUEEN, clr, CordinateToSquare('d', pos), makro} );
        PiecesVector->push_back(new Piece{KING, clr, CordinateToSquare('e', pos), makro}  );
        PiecesVector->push_back(new Piece{BISHOP, clr, CordinateToSquare('f', pos), makro} );
        PiecesVector->push_back(new Piece{KNIGHT, clr, CordinateToSquare('g', pos), makro} );
        PiecesVector->push_back(new Piece{ROOK, clr, CordinateToSquare('h', pos), makro} );
        
    }
}

//* makes changes to global variables such as boardvector and or uses them.
bool doPieceTypeAllContain(PieceColor piececolor, Square* sqr){
    
    for (auto* piece : *PiecesVector)
    {
        
        if (piece->piececolor == piececolor) {
            if (piece->type != KING) UpdateLegalMoves(piece->LegalMoves, piece, History);
            
            for (auto legalmove : piece->LegalMoves)
            {
                if (legalmove.square == sqr) return true;
            }
        }
    }
    
    return false;
}

void UpdateLegalMoves(std::vector<Move>& LegalMoves, Piece* pc, std::vector<Notate*>* history) {
    
    BoardPositionNotation& pos = pc->OnSquare->BoardPosition_notation;

    LegalMoves.clear(); // MAY MESSUP WITH BOARDFLIP
    
    PieceColor& piececolor = pc->piececolor;
    PieceType& type = pc->type;
    
    if (type == PAWN) // DISREGARDING CHECK
    
    {
        Move s1 = Move{PL(pos, 0, (int)piececolor)} ;
        Move s2 = Move(PL(pos, 1, (int)piececolor), TAKE); // left
        Move s3 = Move(PL(pos, -1, (int)piececolor), TAKE); // right
        
        Square* s4{}; // double pawn forward
        // Move* s5 = nullptr; // en pessant
        
        if (

            
            (PL(pos, 0, (int)piececolor) && PL(pos, 0, (int) (piececolor*2) ))
            
            && !PL(pos, 0, (int)piececolor)->HoldingPiece && !PL(pos, 0, (int) (piececolor*2))->HoldingPiece
                                                                                                                                   
                                                                                                                                   ) {
                                                                                                                                       
                                                                                                                                       
                if (piececolor == WHITE) {
                    if (pos.numberCordinate == 2) {
                                                                                                                                                
                        s4 = PL(pos, 0, 2);
                        LegalMoves.push_back( Move{s4, MOVE, DOUBLEFORWARD});
                        
                    }
                }
                    
                else {
                    if (pos.numberCordinate == 7) {
                        s4 = PL(pos, 0, -2);
                        LegalMoves.push_back(   Move{s4,MOVE,DOUBLEFORWARD } );

                    }
                    
                }

                                                                                                                                       
            // lmao i accidentaly typed elseif i was trying to type else then if but i discovered ooga booga its the same thin
        }
        
        // -----
        
        // EN PESSANT
        
        Notate* LatestNotate = nullptr; // works like a charm (no joke actually)
        
         
        if ( history->size() != 0) LatestNotate = (history->at(history->size()-1) );
                                                    // last position
        
        if (LatestNotate && LatestNotate->piece &&
            LatestNotate->NoT != CREATE &&
            LatestNotate->NoT != REMOVE &&
            (LatestNotate->piece->piececolor != piececolor) &&
            (LatestNotate->ADD == DOUBLEFORWARD) &&


            
            (
            ( PL(pos, 1, 0) && (PL(pos, 1, 0)->BoardPosition_notation == LatestNotate->To->BoardPosition_notation) ) ||
            ( PL(pos, -1, 0) && (PL(pos, -1, 0)->BoardPosition_notation == LatestNotate->To->BoardPosition_notation) )
            )
            
            )
        
        {
            LegalMoves.push_back( Move{PL(LatestNotate->To->BoardPosition_notation, 0, piececolor), TAKE, PESSANT  } );
        }
        
        
        
        // * //
            //if (LatestNotate) LatestNotate->print();
        // * //
        
        // ----
          
                                       
        if (s1.square && s1.square->HoldingPiece == nullptr) LegalMoves.push_back(s1);
        if (s2.square && s2.square->HoldingPiece && CanTake(pc, s2.square->HoldingPiece) ) LegalMoves.push_back(s2);
        if (s3.square &&s3.square->HoldingPiece && CanTake(pc, s3.square->HoldingPiece) ) LegalMoves.push_back(s3);
        
                                       
    }
    
    else if (type == KNIGHT) {
        
        vector<Move> legals = {
            PL(pos, 1, 2),
            PL(pos, -1, 2),
            PL(pos, 2, 1),
            PL(pos, -2, -1),
            PL(pos, -2, 1),
            PL(pos, 1, -2),
            PL(pos, -1, -2),
            PL(pos, 2, -1)
        };
        
        for (auto e : legals) {
            
            if (!e.square) continue;
            
            if (e.square->HoldingPiece && !CanTake(pc, e.square->HoldingPiece)) continue;
            
            if (e.square->HoldingPiece && CanTake(pc, e.square->HoldingPiece)) e.type = TAKE;
            
            LegalMoves.push_back(e);
        }
        
    }
    
    else if (type == BISHOP) {
        vector<Move> legals{};
        
        for (int direction = 1; direction <= 4; direction++) {
            
            int a = (direction%2 == 0) ? 1 : -1;
            int b = (direction <= 2) ? 1 : -1;
    
            for (int i = 1 ; true; i++) {
                
                int na = a * i;
                int nb = b * i;
                
                if (!PL(pos, na, nb)) break;
                if ( PL(pos, na, nb)->HoldingPiece != nullptr) {
                    
                    if ( CanTake(pc, PL(pos, na,nb)->HoldingPiece)) {
                        
                        legals.push_back( {PL(pos, na, nb), TAKE} );
                    
                    }
                    
                    break;
                }
                
                legals.push_back(PL(pos, na, nb));
                
            }
            
            
        }
        
        for (auto e : legals)
        {
            if (e.square) LegalMoves.push_back(e);
        }
    }
    
    else if (type == ROOK) {
        vector<Move> legals{};
        
        for (int direction = 1; direction <= 4; direction++) {
            
            int a = (direction%2 == 0) ? 0 : ( (direction==1) ? -1 : 1 ) ;
            int b = (direction%2 != 0) ? 0 : ( (direction==2) ? 1 : -1 ) ;
    
            for (int i = 1 ; true; i++) {
                
                int na = a * i;
                int nb = b * i;
                
                if (!PL(pos, na, nb)) break;
                if ( PL(pos, na, nb)->HoldingPiece != nullptr) {
                    
                    if ( CanTake(pc, PL(pos, na,nb)->HoldingPiece)) legals.push_back( {PL(pos, na, nb), TAKE} );
                    
                    break;
                }
                
                legals.push_back(PL(pos, na, nb));
                
            }
            
            
        }
        
        for (auto e : legals)
        {
            if (e.square) LegalMoves.push_back(e);
        }
    }
    
    else if (type == QUEEN) {
        vector<Move> legals{};
        
        for (int direction = 1; direction <= 9; direction++) {
            
            int a = (direction <= 3) ? -1 : ( (direction <= 6) ? 1 : 0 ) ;
            int b = (direction == 1 || direction == 4 || direction == 8) ? -1 : ( (direction == 2 || direction == 5 || direction == 7) ? 1 : 0 ) ;
    
            for (int i = 1 ; true; i++) {
                
                int na = a * i;
                int nb = b * i;
                
                if (!PL(pos, na, nb)) break;
                if ( PL(pos, na, nb)->HoldingPiece != nullptr) {
                    
                    if ( CanTake(pc, PL(pos, na,nb)->HoldingPiece)) legals.push_back( {PL(pos, na, nb), TAKE} );
                    
                    break;
                }
                
                legals.push_back(PL(pos, na, nb));
                
            }
            
            
        }
        
        for (auto e : legals)
        {
            if (e.square) LegalMoves.push_back(e);
        }
    }
    
    else if (type == KING) { // CASTLING NOT IMPLEMENTED
        vector<Move> legals{};
        
        for (int i = 0; i <= 8; i++) {
            int& direction = i;
            int a = (direction <= 3) ? -1 : ( (direction <= 6) ? 1 : 0 ) ;
            int b = (direction == 1 || direction == 4 || direction == 8) ? -1 : ( (direction == 2 || direction == 5 || direction == 7) ? 1 : 0 ) ;
            
            Move sqr = PL(pos, a, b);
            
            if (!sqr.square) continue;
            
            if (sqr.square->HoldingPiece && !CanTake(pc, sqr.square->HoldingPiece)) continue;
            if (CanTake(pc, sqr.square->HoldingPiece)) sqr.type = TAKE;
            
            legals.push_back(sqr);
            
        }
        
        if (Serious && (Checking == (Check) piececolor) ) // if we are in check
        {
            ;
        }
        
        // remove moves that will result in check
        
        //* bugged 100 out of 100 percent
        
        /*for(int i = 0; i < legals.size(); i++)
        {
            std::cout << piececolor << ' ' << i << '\n';
            Move& e = legals[i];
            
            bool canttk = false;
            
            //if (piececolor == WHITE) canttk = doPieceTypeAllContain(BLACK, e.square);
            //else canttk = doPieceTypeAllContain(WHITE, e.square);
            //std::cout << "canttk = " << canttk << '\n';
             
             
            
            
            //FUTURE method doesn't work.
            
            MoveTo(e, true);
            
            if (piececolor == WHITE)
                canttk = canTakeWhiteKingAll();
            if (piececolor == BLACK)
                canttk = canTakeBlackKingAll();
            
            Move moveback = Move{OldSquare};
            MoveTo(moveback, true);
            
            if (canttk == true) {
                auto it = (legals.begin()+i);
                legals.erase(it);
            }
            
        }*/
        
        for (auto e : legals) {
            if (e.square) LegalMoves.push_back(e);
        }
        
    }
    
    
    
}

// return piece type from int form
PieceType getTypeInf(int inf) {
    
    switch (abs(inf))
    {
        case 1: return PAWN; break;
        case 2: return KNIGHT; break;
        case 3: return BISHOP; break;
        case 4: return ROOK; break;
        case 5: return QUEEN; break;
        case 6: return KING; break;
        default: {
            std::cout << "error inf (int form) from function PieceType getTypeInf(int) is not 1-6 or -1 to -6.\n";
            return PAWN;
        }
    }
}

// returns piece color from int form
PieceColor getColorInf(int inf) {
    if (inf > 1) return WHITE;
    else return BLACK;
}

// intform stands is piece color and type in integer form
// (comments how it works in VirtualBoard.hpp)
void UpdateLegalMoves(std::vector<int>& LegalMoves, int boardIndex, int inf, std::vector<LNotate*>* history, const std::array<int, 64>& intBoard) {

    LegalMoves.clear(); // MAY MESSUP WITH BOARDFLIP
    
    PieceColor piececolor = getColorInf(inf);
    PieceType type = getTypeInf(inf);
    
    int& pos = boardIndex;
    
    if (type == PAWN) // DISREGARDING CHECK
    
    {
        int s1 = PL(pos, 0, (int)piececolor) ;
        int s2 = PL(pos, 1, (int)piececolor); // left (take)
        int s3 = PL(pos, -1, (int)piececolor); // right (take)
        
        if ( PL(pos, 0, (int)piececolor) == 0 && PL(pos, 0, (int) (piececolor*2)) == 0) {
    
                if (piececolor == WHITE) {
                    if (pos >= 49 && pos <= 56) { // number cordinate == 2
                        LegalMoves.push_back(PL(pos, 0, 2));
                        
                    }
                }
                    
                else {
                    if (pos >= 9 && pos <= 16) { // number cordinate == 7

                        LegalMoves.push_back(PL(pos, 0, -2));

                    }
                    
                }

                                                                                                                                       
            // lmao i accidentaly typed elseif i was trying to type else then if but i discovered ooga booga its the same thin
        }
        
        // -----
        
        // EN PESSANT
        
        LNotate* LatestNotate = nullptr; // works like a charm (no joke actually)
        
         
        if ( history->size() != 0) LatestNotate = (history->at(history->size()-1) );
                                                    // last position
        
        if (getColorInf( (LatestNotate->inf) != piececolor)   &&
            (LatestNotate->special == DOUBLEFORWARD) &&


            
            (
            ( (PL(pos, 1, 0) == LatestNotate->To) ) ||
            ( (PL(pos, -1, 0) == LatestNotate->To) )
            )
            
            )
        
        {
            LegalMoves.push_back( PL(LatestNotate->To, 0, piececolor) ); // PESSANT
        }
        
        
        
        // * //
            //if (LatestNotate) LatestNotate->print();
        // * //
        
        // ----
          
        
        if (intBoard[s1] == 0) LegalMoves.push_back(s1);
        if (intBoard[s2] != 0 && CanTake(boardIndex, inf, s2, intBoard[s2]) ) LegalMoves.push_back(s2);
        if ( intBoard[s3] != 0 && CanTake(boardIndex, inf, s3, intBoard[s3]) ) LegalMoves.push_back(s3);
        
                                       
    }
    
    else if (type == KNIGHT) {
        
        std::array<int, 8> legals = {
            PL(pos, 1, 2),
            PL(pos, -1, 2),
            PL(pos, 2, 1),
            PL(pos, -2, -1),
            PL(pos, -2, 1),
            PL(pos, 1, -2),
            PL(pos, -1, -2),
            PL(pos, 2, -1)
        };
        
        for (auto e : legals) {
            
            if (e == -1) continue; // if it goes outside of board.
            
            if (intBoard[e] != 0 && !CanTake(boardIndex, intBoard[boardIndex], e, intBoard[e])) continue;
            
            //if (intBoard[e] && CanTake(boardIndex, intBoard[boardIndex], e, intBoard[e])) e.type = TAKE;
            
            LegalMoves.push_back(e);
        }
        
    }
    
    else if (type == BISHOP) {
        vector<int> legals{};
        
        for (int direction = 1; direction <= 4; direction++) {
            
            int a = (direction%2 == 0) ? 1 : -1;
            int b = (direction <= 2) ? 1 : -1;
    
            for (int i = 1 ; true; i++) {
                
                int na = a * i;
                int nb = b * i;
                
                if (!PL(pos, na, nb)) break;
                if ( intBoard[PL(pos, na, nb)] != 0) {
                    
                    if ( CanTake(boardIndex, intBoard[boardIndex], PL(pos, na,nb), intBoard[PL(pos, na,nb)])) {
                        
                        legals.push_back(PL(pos, na, nb));
                    
                    }
                    
                    break;
                }
                
                legals.push_back(PL(pos, na, nb));
                
            }
            
            
        }
        
        for (auto e : legals)
        {
            if (e != -1) LegalMoves.push_back(e);
        }
    }
    
    else if (type == ROOK) {
        vector<int> legals{};
        
        for (int direction = 1; direction <= 4; direction++) {
            
            int a = (direction%2 == 0) ? 0 : ( (direction==1) ? -1 : 1 ) ;
            int b = (direction%2 != 0) ? 0 : ( (direction==2) ? 1 : -1 ) ;
    
            for (int i = 1 ; true; i++) {
                
                int na = a * i;
                int nb = b * i;
                
                if (PL(pos, na, nb) == -1) break;
                if ( intBoard[PL(pos, na, nb)] != 0) {
                    
                    if ( CanTake(boardIndex, intBoard[boardIndex], PL(pos, na,nb), intBoard[PL(pos, na,nb)])) legals.push_back( PL(pos, na, nb) );
                    
                    break;
                }
                
                legals.push_back(PL(pos, na, nb));
                
            }
            
            
        }
        
        for (auto e : legals)
        {
            if (e != -1) LegalMoves.push_back(e);
        }
    }
    
    else if (type == QUEEN) {
        vector<int> legals{};
        
        for (int direction = 1; direction <= 9; direction++) {
            
            int a = (direction <= 3) ? -1 : ( (direction <= 6) ? 1 : 0 ) ;
            int b = (direction == 1 || direction == 4 || direction == 8) ? -1 : ( (direction == 2 || direction == 5 || direction == 7) ? 1 : 0 ) ;
    
            for (int i = 1 ; true; i++) {
                
                int na = a * i;
                int nb = b * i;
                
                if (PL(pos, na, nb) == -1) break;
                if ( intBoard[PL(pos, na, nb)] != 0) {
                    
                    if ( CanTake(boardIndex, intBoard[boardIndex], PL(pos, na,nb), intBoard[PL(pos, na,nb)])) legals.push_back(PL(pos, na, nb) );
                    
                    break;
                }
                
                legals.push_back(PL(pos, na, nb));
                
            }
            
            
        }
        
        for (auto e : legals)
        {
            if (e != -1) LegalMoves.push_back(e);
        }
    }
    
    else if (type == KING) { // CASTLING NOT IMPLEMENTED
        vector<int> legals{};
        
        for (int i = 0; i <= 8; i++) {
            int& direction = i;
            int a = (direction <= 3) ? -1 : ( (direction <= 6) ? 1 : 0 ) ;
            int b = (direction == 1 || direction == 4 || direction == 8) ? -1 : ( (direction == 2 || direction == 5 || direction == 7) ? 1 : 0 ) ;
            
            int sqr = PL(pos, a, b);
            
            if (sqr == -1) continue;
            
            if (intBoard[sqr] != 0 && !CanTake(boardIndex, intBoard[boardIndex], sqr, intBoard[sqr])) continue;
            //if (CanTake(boardIndex, intBoard[boardIndex], sqr, intBoard[sqr])) sqr.type = TAKE;
            
            legals.push_back(sqr);
            
        }
        
        if (Serious && (Checking == (Check) piececolor) ) // if we are in check
        {
            ;
        }
        
        // remove moves that will result in check
        
        //* bugged 100 out of 100 percent
        
        /*for(int i = 0; i < legals.size(); i++)
        {
            std::cout << piececolor << ' ' << i << '\n';
            Move& e = legals[i];
            
            bool canttk = false;
            
            //if (piececolor == WHITE) canttk = doPieceTypeAllContain(BLACK, e.square);
            //else canttk = doPieceTypeAllContain(WHITE, e.square);
            //std::cout << "canttk = " << canttk << '\n';
             
             
            
            
            //FUTURE method doesn't work.
            
            MoveTo(e, true);
            
            if (piececolor == WHITE)
                canttk = canTakeWhiteKingAll();
            if (piececolor == BLACK)
                canttk = canTakeBlackKingAll();
            
            Move moveback = Move{OldSquare};
            MoveTo(moveback, true);
            
            if (canttk == true) {
                auto it = (legals.begin()+i);
                legals.erase(it);
            }
            
        }*/
        
        for (auto e : legals) {
            if (e != -1) LegalMoves.push_back(e);
        }
        
    }
    
    
    
}
