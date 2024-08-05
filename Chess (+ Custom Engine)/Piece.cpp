#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "GLOBAL.h"
#include "Square.h"
#include "BoardPosition.h"
#include "FUNCTIONS.h"
#include "Piece.h"

#define UL ++
#define DR --

#define outlinethickness 10
#define outlinecolor 255, 255, 255, 127

using namespace std;
using namespace sf;

// maybe this is responsible for when a square's rec is highlighted and it
// wants to go back to it's original form
const Color& Piece::GetCorrectMoveColor(const Color& OtherRecColor) {
    if (OtherRecColor == (Color) 0xeeeed2ff) { // white
        return WHITEMoveColor;
    }
    
    if (OtherRecColor == (Color) 0x779656ff) { // dark
        return DARKMoveColor;
    }
    
    return OtherRecColor;
}

void Piece::UpdateTexture() {
    
    // WARNING: DOESNT USE THE /IMAGES/ HERE
    
    string r = "/Users/quirixwastaken/Documents/XCode Projects/Chess (+ Custom Engine)/Images/";
    
    if (piececolor == BLACK) r += "black_";
    else r += "white_";
    
    switch (type) {
        case PAWN: r += "pawn"; break;
        case KNIGHT: r += "knight"; break;
        case BISHOP: r += "bishop"; break;
        case ROOK: r += "rook"; break;
        case QUEEN: r += "queen"; break;
        case KING: r += "king"; break;
        default: cout << "DEFAULT: ERROR\n";
    }
    
    r += ".png";
    
    texture.loadFromFile(r);
    rec->setTexture(&texture);
}

Piece::Piece(RenderWindow* w,
             vector<Square*>* bv,
             vector<Piece*>* pv, vector<Notate*>* hs) {
    
    window = w;
    BoardVector = bv;
    PiecesVector = pv;
    History = hs;
    
    /*hoveringIconTexture->loadFromFile("/Users/quirixwastaken/Documents/XCode Projects/Chess (+ Custom Engine)/Images/half_niggaballs.png");
    
    hoveringIconSprite->setTexture(hoveringIconTexture);*/
    
    // "hoveringIconSprite" is a rectangle
    hoveringIconSprite->setFillColor(Color::Transparent);
    hoveringIconSprite->setOutlineColor(Color{outlinecolor} );
    hoveringIconSprite->setOutlineThickness(outlinethickness);
    
    /*Square* element = SquareTouchingMouse();
    
    hoveringIconSprite->setPosition( element->rec->getPosition().x, element->rec->getPosition().y);*/
    
    
    rec = new RectangleShape(Vector2f(squareWidth, squareHeight) );
    type = PAWN;
    piececolor = WHITE;
    
    UpdateTexture();
}

Piece::Piece(PieceType arg_piecetype, PieceColor arg_piececolor, Square* arg_onsquare,
             RenderWindow* w,
             vector<Square*>* bv,
             vector<Piece*>* pv, vector<Notate*>* hs) {
    
    window = w;
    BoardVector = bv;
    PiecesVector = pv;
    History = hs;

    
    hoveringIconSprite->setFillColor(Color::Transparent);
    hoveringIconSprite->setOutlineColor(Color{outlinecolor} );
    hoveringIconSprite->setOutlineThickness(outlinethickness);
    
    rec = new RectangleShape(Vector2f(squareWidth, squareHeight) );
    type = arg_piecetype;
    piececolor = arg_piececolor;
    
    UpdateTexture();
    
    Move dm = {arg_onsquare};
    dm.type = CREATE;
    
    MoveTo(dm);
}


/*
 
    the function below uses class Move as argument to move the piece to the position
    and/or take another piece and move, en pessant, and other stuff.
    it also updates legalmoves (with UpdateLegalMoves()).
 
 */

void Piece::MoveTo(Move& var_square, bool future) {
    
    
    
    bool took = (var_square.type == TAKE);
    bool backRcreate = ( (OnSquare == var_square.square) || (var_square.type == CREATE) );
    
    Vector2f recpos = var_square.square->rec->getPosition();
    //Vector2f recsize = var_square.square->rec->getSize();
    
    if (OnSquare) {
        OnSquare->UpdateHoldingPiece(nullptr);
    }
    
    if (var_square.type == TAKE) {
        
        if (var_square.special == PESSANT) {
            (PL(var_square.square->BoardPosition_notation, 0, -piececolor))->HoldingPiece->die();
        }
        
        else var_square.square->HoldingPiece->die();
    }
    
    OldSquare = OnSquare;
    
    //##debug
    //std::cout << "equation1: " << recpos.x << '\n';
    //std::cout << "equation2: " << recpos.x + (recsize.x - rec->getSize().x) << '\n';
    //std::cout << "equation3: " << recpos.x + (recsize.x - rec->getSize().x) / 2 << '\n';
    //##debug
    
    
    
    // *****
    // huge problem to fix is with future
    // do what i did with tictactoe
    // *****
    
    if (!future) rec->setPosition( recpos.x/* + (recsize.x - rec->getSize().x) /2*/ , recpos.y + 5);
    OnSquare = var_square.square;
    var_square.square->UpdateHoldingPiece(this);
    
    if (OldSquare && OnSquare && OldSquare == OnSquare) OldSquare = nullptr;
    
    /*else*/ if (!future) UpdateLegalMoves(LegalMoves, this, History);
    
    if (!future && CanTakeOppositeKing() && Serious) {
        Checking = (Check) -piececolor;
    }
    
    TypeNoT tn = (!took) ? MOVE : TAKE; // what the hell was i thinking here.
    
    if (!backRcreate) History->push_back( new Notate{tn, OldSquare, OnSquare, var_square.special} );
    
}

void Piece::Update() {
    Vector2i mousepos = Mouse::getPosition(*window);
    
    if (IsBeingDragged) {
        
        // set our pointer on Pieces to be at the last position, so it can be drawn at top of the pieces
        
        int indexOnPiecesVector = -1;
        
        {
            
            int i = 0;
            
            for (auto* element : *PiecesVector) {
                ++i;
                if (element != this) continue;
                
                indexOnPiecesVector = i;
                break;
            }
                    
        }
        
        // if it isn't already on the last position
        if (indexOnPiecesVector != PiecesVector->size())
        
        {
            
            // puts piece pointer to the last position
            PiecesVector->erase(PiecesVector->begin() + (indexOnPiecesVector-1) );
            PiecesVector->insert(PiecesVector->begin() + (PiecesVector->size()), this);
        }
        
        
        
        rec->setPosition(mousepos.x, mousepos.y);
        
        Square* element = SquareTouchingMouse();
        
        if (!element) return; // if mouse is not touching any square (e.g outside of window) return
        
        // set the hoveringIconSprite rectangle to the position of where the is mouse touching
        hoveringIconSprite->setPosition( element->rec->getPosition().x + outlinethickness, element->rec->getPosition().y + outlinethickness);
        hoveringIconSprite->setSize( Vector2f(squareWidth - outlinethickness*2, squareHeight - outlinethickness*2) );
    }
    
}

bool Piece::OnMouseRelease(bool isTurn = true) {
    
    if (OldSquare) OldSquare->rec->setFillColor(OldSquare->defaultColor);
    
    if (isTurn) {
        if (IsBeingDragged) {
            
            // no idea how setOrigin works but it does, search for it later
            rec->setOrigin(0, 0);
            IsBeingDragged = false;
            
            Square* b = nullptr;
            
            b = SquareTouchingMouse();
            
            
            // if DissallowLegalMoves is true then every move is legal regardless of the things below
            // currently doesent work though
            bool islegal = DissallowLegalMoves;
            
            Move move;
            
            for (auto e : LegalMoves) {
                
                // if SquareTouchingMouse is nullptr e.g mouse outside of window, break
                if (!b) break;
                // if SquareTouchingMouse square is on the LegalMoves vector (LegalMoves[0].square) then islegal = true
                // and set the move variable to that legal move.
                if (e.square == b) { islegal = true; move = e; break; }
            }
            
            // if not legal then -> move to it's square that it is right now
            if (!islegal) {
                
                Move a = {OnSquare};
                
                MoveTo(a);
                return false;
            }
            
            MoveTo(move);
            
            /*
               piece moves, and this if statement below says that if
               piececolor is white (1) and checking is black to white (1)
               and the opposite, then the checking variable is set to nocheck.
            */
            
            if (type == KING && (int)piececolor == (int) Checking)
                Checking = NOCHECK; // if legalmoves work then this works too
            
            return true;
            
        }
    }
    
    
    return false;
}

void Piece::OnMousePress(bool isTurn = true) {
    
    if (isTurn) {
        if ( (Checking == (Check) piececolor) && (type != KING) ) {}
        // if we are in check, and we are not a king piece type
        
        else {
            UpdateLegalMoves(LegalMoves, this, History);
            
            if (IsMouseInRec(rec)) {
                rec->setOrigin(rec->getSize().x/2, rec->getSize().y/2);
                IsBeingDragged = true;
                
                OnSquare->rec->setFillColor(GetCorrectMoveColor(OnSquare->rec->getFillColor()));
                if (OldSquare) OldSquare->rec->setFillColor(OldSquare->defaultColor);
                
                return;
            }
        }
        
    }
    
    if (OnSquare) OnSquare->rec->setFillColor(OnSquare->defaultColor);
    if (OldSquare) OldSquare->rec->setFillColor(OldSquare->defaultColor);
    
    
    
}

void Piece::draw() {
    
    if (hoveringIconSprite && IsBeingDragged) {
        window->draw(*hoveringIconSprite);
    }
    
    if (IsBeingDragged && !DissallowLegalMoves) {
        
        // assuming legalsquares is updated
        
        for (auto e : LegalMoves) {
            Vector2f pos;
            
            if (e.square) pos = e.square->rec->getPosition(); 
            
            CircleShape circle{};
            circle.setRadius(25);
            circle.setFillColor(Color(0,0,0, 30));
            circle.setPosition(pos.x + 25, pos.y + 25);
            
            window->draw(circle);
        }
        
    }
    
    if (rec != nullptr)
        window->draw(*rec);
    
}

Piece::~Piece() {
    if (hoveringIconTexture) delete hoveringIconTexture;
    if (rec) delete rec;
    if (OnSquare) OnSquare->rec->setFillColor(OnSquare->defaultColor);
    
    hoveringIconTexture = nullptr;
    hoveringIconSprite=nullptr;
    rec=nullptr;
}

void Piece::die() {
    if (OnSquare) OnSquare->rec->setFillColor(OnSquare->defaultColor);
    if (OldSquare) OldSquare->rec->setFillColor(OldSquare->defaultColor);
    if (OnSquare) { OnSquare->UpdateHoldingPiece(nullptr); OnSquare = nullptr; }
    
    for (int i = 0; i < PiecesVector->size(); i++) {
        if ( (*PiecesVector)[i] == this) PiecesVector->erase(PiecesVector->begin() + i);
    }
    
    delete this;
}

bool Piece::CanTakeOppositeKing() {
    if (type != KING) UpdateLegalMoves(LegalMoves, this, History);
    
    for (auto legalmove : LegalMoves) // type: Move
    {
        
        Piece* lgmPiece = legalmove.square->HoldingPiece;
        
        if (lgmPiece && lgmPiece->piececolor != piececolor &&
            lgmPiece->type == KING) return true;
            
    }
    
    return false;
}
