#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


#include "BoardPosition.h"
#include "Piece.h"
#include "Notate.hpp"

using namespace std;
using namespace sf;

class Piece;
class BoardPositionNotation;

class Square {
    
    RenderWindow* window;
    vector<Square*>* BoardVector;
    vector<Piece*>* PiecesVector;
    vector<Notate*>* History;
    
public:
    RectangleShape* rec = nullptr;
    Color defaultColor;
    Piece* HoldingPiece = nullptr; // nullptr for none
    
    int BoardPosition_num;
    BoardPositionNotation BoardPosition_notation;
    
    bool MousePressInRec = false;
    bool HoldingNoInRec = false;
    
    Square(RectangleShape* r,RenderWindow* w,
           vector<Square*>* bv,
           vector<Piece*>* pv, vector<Notate*>* hs);
    
    Square(RenderWindow* window,
           vector<Square*>* BoardVector,
           vector<Piece*>* PiecesVector, vector<Notate*>* hs);
    
    void OnMousePressEventHandler();
    
    void OnMouseReleaseEventHandler();
    
    void SetDefaultColor();
    void SetBoardPosition(int e);
    
    void UpdateHoldingPiece(Piece* piece);
    
    void update();
    
    void draw();
    
};
