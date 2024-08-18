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
#include "LNotate.hpp"

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
int PL(int, int, int);

bool canTakeBlackKingAll();
bool canTakeWhiteKingAll();

// if any white piece can take the black king
bool canTakeBlackKingAll(const std::array<int, 64>& intBoard, std::array<LNotate, 50>& history, std::array<int, 2>&);
// if any black piece can take the white king
bool canTakeWhiteKingAll(const std::array<int, 64>& intBoard, std::array<LNotate, 50>& history, std::array<int, 2>&);
// both functions are function overloads for int form.

// can take (opposite color) king
bool canTakeKingInf(const std::array<int, 64>& intBoard, int index, std::array<LNotate, 50>& history, std::array<int, 2>&);

// do any of the pieces with a (variable) piece color have sqr (variable) in them
bool doPieceTypeAllContain(PieceColor, Square* sqr);

// function overload for int form.
bool doPieceTypeAllContain(PieceColor, int sqrindex, std::array<int, 64>& intBoard, std::array<LNotate, 50>& history, std::array<int, 2>&);

void putPiecesInBoard();

void UpdateLegalMoves(std::vector<Move>&, Piece*, std::vector<Notate*>*, std::array<int, 2>& cstl=castleState);

void UpdateLegalMoves(std::vector<int>& LegalMoves, int boardIndex, int inf, std::array<LNotate, 50>* history, const std::array<int, 64>& intBoard, std::array<int, 2>&);

PieceType getTypeInf(int);
// Inf stands for int form

PieceColor getColorInf(int);
// Inf stands for int form

int findColumn(int);
int findRow(int);

int normalToInf(PieceType type, PieceColor clr);

void updateCastleStateInf(int inf, int from, std::array<int, 2>& castleSt);

void moveInfPiece(std::array<int, 64>& intBoard, const LNotate& nt, std::array<LNotate, 50>& history, int& count, std::array<int, 2>& castleSt);

bool checkForCastlingInf(int pos, std::array<int, 64>& intBoard, std::array<LNotate, 50>& history, std::array<int, 2>& castleSt);
