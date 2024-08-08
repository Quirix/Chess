#pragma once

#include "Square.h"
#include "Piece.h"
#include <string>
#include "GLOBAL.h"
#include "LNotate.hpp"

using namespace std;

class Square;
class Piece;

// enum AddNoT?

class Notate {
public:
    
    TypeNoT NoT;
    AddNoT ADD;
    
    Square* From;
    Square* To;
    Piece* piece; // gather from To->holdingPiece (if holdingpiece)
    
    Notate(TypeNoT, Square*, Square*, AddNoT j = CLASSIC);
    
    void print(string e="\n");
    string sprint();
    LNotate getLNotateVersion();
    void changeLNotate(LNotate&);
};
