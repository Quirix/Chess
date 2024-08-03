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
            if (piece->type != KING) piece->UpdateLegalMoves();
            
            for (auto legalmove : piece->LegalMoves)
            {
                if (legalmove.square == sqr) return true;
            }
        }
    }
    
    return false;
}

