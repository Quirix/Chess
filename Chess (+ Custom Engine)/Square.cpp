#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "GLOBAL.h"
#include "Square.h"
#include "BoardPosition.h"
#include "FUNCTIONS.h"
#include "Piece.h"

#define makro window, BoardVector, PiecesVector

Square::Square(RectangleShape* r, RenderWindow* w,
                                         vector<Square*>* bv,
                                         vector<Piece*>* pv, vector<Notate*>* hs): defaultColor{r->getFillColor()} {
    
    window = w;
    BoardVector = bv;
    PiecesVector = pv;
    History = hs;
    
    rec = r;
}

Square::Square(RenderWindow* w,
               vector<Square*>* bv,
               vector<Piece*>* pv, vector<Notate*>* hs)

{
    window = w;
    BoardVector = bv;
    PiecesVector = pv;
    History = hs;
}

void Square::OnMousePressEventHandler() {
    
    if (IsMouseInRec(rec
                     
        )) {
        MousePressInRec = true;
    }
    
}

void Square::OnMouseReleaseEventHandler() {
    
    MousePressInRec = false;
}

void Square::SetDefaultColor() { defaultColor = rec->getFillColor(); }

void Square::SetBoardPosition(int e) {
    BoardPosition_num = e;
    BoardPosition_notation = NumberToNotation(e);
    
}

void Square::UpdateHoldingPiece(Piece* piece) {
    HoldingPiece = piece;

}

void Square::update() {
    
    /*if (rec != nullptr && IsMousePressedInRec(*window) == true) {
        Piece* e = new Piece;
        e->MoveTo(*this);
        PiecesVector.push_back(e);
        cout << "Created piece on " << BoardPosition_notation.PrintOutString()<<'\n';
    }*/
    
}

void Square::draw() {
    window->draw(*rec);
}

