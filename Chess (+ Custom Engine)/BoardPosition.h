#pragma once

#include <string>

using namespace std;
using namespace sf;

class BoardPositionNotation {
public:
    
    char characterCordinate{};
    int numberCordinate{};
    
    BoardPositionNotation(char a, int b);
    BoardPositionNotation();
    
    void PrintOut();
    
     string PrintOutString();
};

bool operator==( BoardPositionNotation& a,  BoardPositionNotation& b);
