#include "GLOBAL.h"
#include "Piece.h"
#include "Square.h"


int WindowWidth = 800;
int WindowHeight = 800;

float squareWidth = 0;
float squareHeight = 0;

bool DissallowLegalMoves = false;
// set to true if you want every move to be legal
// current broken :: doesent work

bool TakeTurns = true;
bool CanCreate = false;
bool Serious = true; // non-debug

std::array<int, 2> castleState {2, 2};

Check Checking = NOCHECK;
