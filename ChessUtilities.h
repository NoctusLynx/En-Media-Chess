#ifndef CHESS_UTILITIES
#define CHESS_UTILITIES

#include <stdbool.h>

// Board Assessment
char* ChessPiece(char code[3]);
bool IsOnBoard(int input);
bool SpaceOccupied(char* boardSpace);
bool Check(char* board[8][8], int posX, int posY, bool debug);

// Piece placement
void PlacePawns(char* board[8][8], int bonusIterations[4], bool debug);
void PlaceRooks(char* board[8][8], int extraRooks, bool debug);
void PlaceBishops(char* board[8][8], int extraBishops, bool debug);
void PlaceKnights(char* board[8][8], int extraKnights, bool debug);
void PlaceQueens(char* board[8][8], int extraQueens, bool debug);
void PlaceKing(char* board[8][8], bool debug);

// Text Output
void CheckMessage(char* checkingPiece, int posX, int posY, int kingX, int kingY);
void PlacementMessage(char* placedPiece1, char* placedPiece2, int posX, int posY);

#endif