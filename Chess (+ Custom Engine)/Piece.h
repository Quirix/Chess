#pragma once

#include <SFML/Graphics.hpp>
#include <vector>



#include "BoardPosition.h"
#include "Square.h"
#include "GLOBAL.h"
#include "Notate.hpp"
#include "Move.hpp"

class Notate;
 
using namespace std;
using namespace sf;

class Square;
class BoardPositionNotation;
class Move;

class Piece {
private:
    
    const Color WHITEMoveColor = Color(0xEFEFC3ff);
    const Color DARKMoveColor = Color(0x7F9F53ff);
    
    RenderWindow* window;
    vector<Square*>* BoardVector;
    vector<Piece*>* PiecesVector;
    vector<Notate*>* History;
    
    void UpdateTexture();
    const Color& GetCorrectMoveColor(const Color& OtherRecColor);
    
public:
    
    vector<Move> LegalMoves{};
    
    Texture texture;
    PieceColor piececolor;
    RectangleShape* rec;
    PieceType type;
    
    Square* OldSquare = nullptr;
    Square* OnSquare = nullptr;
    
    Texture* hoveringIconTexture = new Texture;
    RectangleShape* hoveringIconSprite = new RectangleShape;
    
    bool InitiatingFade = false;
    bool IsBeingDragged = false;
    
    int stage = 0; // 0 = fadeout, 1 = fadein, 2 = end
    int AnimationAlpha = 255;
    
    Piece(PieceType arg_piecetype, PieceColor arg_piececolor, Square* arg_onsquare,
          RenderWindow* w,
          vector<Square*>* bv,
          vector<Piece*>* pv, vector<Notate*>* hs);
    
    Piece(RenderWindow* w,
          vector<Square*>* bv,
          vector<Piece*>* pv, vector<Notate*>* hs);
    void die(); // use when piece takes piece2, piece2.die();
    void MoveTo(Move& var_square);
    
    bool CanTakeOppositeKing();
    
    void OnMousePress(bool);
    bool OnMouseRelease(bool);
    
    void Update();
    void draw();
    
    ~Piece();
};


