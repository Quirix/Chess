#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "GLOBAL.h"
#include "Square.h"
#include "BoardPosition.h"
#include "FUNCTIONS.h"
#include "Piece.h"

BoardPositionNotation::BoardPositionNotation(char a, int b): characterCordinate{a}, numberCordinate{b} {;}
BoardPositionNotation::BoardPositionNotation() {;};
void BoardPositionNotation::PrintOut() {
    cout << characterCordinate << "" << numberCordinate;
}

 string BoardPositionNotation::PrintOutString() {
    string r = "";
    r += characterCordinate;
    r += to_string(numberCordinate);
    return r;
}

bool operator==( BoardPositionNotation& a,  BoardPositionNotation& b) {
    return ((a.characterCordinate == b.characterCordinate) && (a.numberCordinate == b.numberCordinate));
}
