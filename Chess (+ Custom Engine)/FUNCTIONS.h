#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "GLOBAL.h"
#include "BoardPosition.h"
#include "Piece.h"
#include "Square.h"
#include "Notate.hpp"

using namespace std;
using namespace sf;

class BoardPositionNotation;
class Piece;
class Square;
class Notate;

void AssignStuff(RenderWindow* w, vector<Square*>* bv, vector<Piece*>* pv, vector<Notate*>* hs);

BoardPositionNotation NumberToNotation(int number);

Square* SquareTouchingMouse();

bool CanTake(Piece* attacker,Piece* piece2);

void EmptyFunction();

bool isMouseDragging();

bool IsMouseInRec(RectangleShape* rec);

bool IsMousePressed();

int NotationToNumber(char CharacterCordiante, int NumberCordiante);

void SetUpBoardVector();

void CheckMouse();

Square* CordinateToSquare(BoardPositionNotation n);
Square* CordinateToSquare(char a,int b);
Square* wcCordinateToSquare(BoardPositionNotation n);

Square* PL(BoardPositionNotation, int, int);

bool canTakeBlackKingAll();
bool canTakeWhiteKingAll();

bool doPieceTypeAllContain(PieceColor, Square* sqr);

bool canTakeWhiteKingAll();

void putPiecesInBoard();

