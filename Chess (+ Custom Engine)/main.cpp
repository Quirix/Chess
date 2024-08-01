//
//  main.cpp
//  Chess (+ Custom Engine)
//
//  Created by Quirix Wastaken on 20/3/23.
//

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <vector>
#include <string>

#include "Piece.h"
#include "Square.h"
#include "BoardPosition.h"
#include "FUNCTIONS.h"
#include "GLOBAL.h"
#include "Notate.hpp"

#define makro &window, &BoardVector, &PiecesVector, &History
#define bpn BoardPositionNotation

using namespace std;
using namespace sf;

enum ModePlacement {
    AUTO,
    FULL
};

int main(){
    
    RenderWindow window(VideoMode(WindowWidth, WindowHeight), "Chess", Style::Close);
    
    vector<Piece*> PiecesVector{};
    vector<Square*> BoardVector{};
    
    vector<Notate*> History{};
    
    
    AssignStuff(makro);
    SetUpBoardVector();
    
    string KeySentence{};
    ModePlacement Placement = AUTO;
    PieceType AutoChoosedType = PAWN;
    PieceColor AutoChoosedColor = WHITE;
    Square* SquareClickedOn = nullptr;
    
    PieceColor Turn = WHITE;
    
    if (Serious)
    {
        TakeTurns = true;
        CanCreate = false;
        DissallowLegalMoves = false;
        
        putPiecesInBoard();
        
    }
    
    while (window.isOpen()) {
        Event event;
        
        while (window.pollEvent(event)) {
            
            switch (event.type) {
                    
                case Event::Closed: {
                    window.close();
                }break;
                    
                
                    
                case Event::MouseButtonPressed: {
                    Square* varSqrTouchingMouse = SquareTouchingMouse();
                    if (varSqrTouchingMouse && !varSqrTouchingMouse->HoldingPiece) SquareClickedOn = varSqrTouchingMouse;
                    
                    for (auto* element : PiecesVector)
                    {
                        element->OnMousePress( (element->piececolor == Turn) );
                    }
                    for (auto* element : BoardVector) element->OnMousePressEventHandler();
                } break;
                   
                
                
                    
                case Event::MouseButtonReleased: {
                    
                    if (Placement == AUTO && CanCreate) {
                        
                        {
                            
                            Square* squareTouchingMouse = SquareTouchingMouse();
                            
                            if (squareTouchingMouse)
                            {
                            
                                Piece* holdingpiece = squareTouchingMouse->HoldingPiece;
                                
                                if (!holdingpiece && !!SquareClickedOn && SquareClickedOn == squareTouchingMouse)  {
                                    Piece* piece = new Piece{AutoChoosedType, AutoChoosedColor, squareTouchingMouse, makro};
                                    
                                    
                                    SquareClickedOn = nullptr;
                                    
                                    History.push_back(new Notate(CREATE, nullptr, piece->OnSquare) );
                                    
                                    PiecesVector.push_back(piece);
                                }
                                
                                
                                
                            }
                        
                        }
                    }
                    
                    for (auto* element : PiecesVector) {
                        if (element->piececolor == Turn) {
                            if (element->OnMouseRelease())
                                Turn = (PieceColor) -Turn;
                        }
                    }
                    for (auto* element : BoardVector) element->OnMouseReleaseEventHandler();
                    
                }  break;
            
                
                    
                case Event::KeyPressed: {
                    if (CanCreate) {
                        int key = event.key.code;
                        
                        if (key == 59) { KeySentence.clear(); break; } // backspace
                        if (key == 57) { KeySentence += ' '; break;} // space
                        
                        KeySentence += (char) (97 + key); // 97+0 = a
                        
                        if (KeySentence == "d" || KeySentence == "destroy") {
                            Piece* holdpiece = SquareTouchingMouse()->HoldingPiece;
                            
                            if (!holdpiece) break;
                            
                            History.push_back(new Notate(REMOVE, holdpiece->OnSquare, nullptr));
                            
                            holdpiece->die();
                            
                            KeySentence.clear();
                            
                        }
                        
                        if (KeySentence.rfind("mode") == 0) {
                            if (KeySentence.rfind("auto") == 8) {
                                Placement = AUTO;
                                KeySentence.clear(); break; }
                            else if (KeySentence.rfind("full") == 8) {
                                Placement = FULL;
                                KeySentence.clear(); break; }
                        } // cant figure out why rfind("full") or auto is at index 8.
                        // mode(xxxx)full
                        // mode(xxxx)auto
                        // dont include the parenthesis in the input. You can put anything where
                        // the parenthesis are but it has to be of length 4.
                        
                        if (KeySentence == "create board") {
                            
                            putPiecesInBoard();
                            KeySentence.clear();
                            
                            break;
                        }

                        //
                                
                        PieceType type;
                        PieceColor color;
                                
                        if (Placement == FULL) {
                        
                            if (KeySentence.rfind("white") == 0 || KeySentence[0] == 'w') color = WHITE;
                            else if (KeySentence.rfind("black") == 0 || KeySentence[0] == 'b') color = BLACK;
                            else break;
                            
                            if (KeySentence.rfind("pawn") == 6 || KeySentence[1] == 'p') type = PAWN;
                            else if (KeySentence.rfind("knight") == 6 || KeySentence[1] == 'n') type = KNIGHT;
                            else if (KeySentence.rfind("bishop") == 6 || KeySentence[1] == 'b') type = BISHOP;
                            else if (KeySentence.rfind("rook") == 6 || KeySentence[1] == 'r') type = ROOK;
                            else if (KeySentence.rfind("queen") == 6 || KeySentence[1] == 'q') type = QUEEN;
                            else if (KeySentence.rfind("king") == 6 || KeySentence[1] == 'k') type = KING;
                            else break;
                            
                            {
                                Piece* holdingpiece = SquareTouchingMouse()->HoldingPiece;
                                
                                if (holdingpiece)  {
                                    KeySentence.clear();
                                    break;
                                }
                            
                            }
                            
                            Piece* piece = new Piece{type, color, SquareTouchingMouse(), makro};
                            
                            PiecesVector.push_back(piece);
                            
                            
                        }
                        
                        else { // Warning: no shortcuts
                            if (KeySentence.rfind("white") == 0) AutoChoosedColor = WHITE;
                            else if (KeySentence.rfind("black") == 0) AutoChoosedColor = BLACK;
        
                            else if (/*KeySentence.rfind("pawn") == 0 ||*/ KeySentence == "p") AutoChoosedType = PAWN;
                            else if (KeySentence.rfind("knight") == 0 || KeySentence == "n") AutoChoosedType = KNIGHT;
                            else if (/*KeySentence.rfind("bishop") == 0 ||*/ (KeySentence == "bi")) AutoChoosedType = BISHOP;
                            else if (/*KeySentence.rfind("rook") == 0 ||*/ KeySentence == "r") AutoChoosedType = ROOK;
                            else if (/*KeySentence.rfind("queen") == 0||*/ KeySentence == "q") AutoChoosedType = QUEEN;
                            else if (/*KeySentence.rfind("king") == 0||*/ KeySentence == "k") AutoChoosedType = KING;
                            else break;
                        }
                        
                        KeySentence.clear();
                    
                        /*
                        
                         if placement is auto then possible input could be
                         white, black, p(pawn), knight || n, bi(bishop),
                         r(rook), q(queen), k(king).
                         
                         if placement is full then also possible input could be
                         white rook, black rook, white queen, black queen,
                         white pawn, black pawn, white king, black king,
                         white bishop, black bishop, white knight, black
                         knight.
                         
                         */
                    }
                } break;
            
                default: {;}
                
                    
            } // switch
            
        } // pollevent
        
        // Update
        
        //##debug###
        //for (auto* e : History) e->print(" ");
        //cout << '\n';
        //std::cout << (int) Checking << '\n';
        //std::cout << PiecesVector.size() << '\n';
        //##debug###
        
        for (auto* element : BoardVector) element->update();
        for (auto* element : PiecesVector) element->Update();
        
        window.clear();
        
        // Draw
        
        for (auto* element : BoardVector) element->draw();
        for (auto* element : PiecesVector) element->draw();
        
        //
        
        window.display();
        
    }
    
    
    

}
