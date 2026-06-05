#ifndef CHESS_UTILITIES
#define CHESS_UTILITIES

#include <stdbool.h>

// Board Assessment
char* ChessPiece(char code[3]);
bool IsOnBoard(int input);
bool SpaceOccupied(char* boardSpace);
bool Check(char* board[8][8], int posX, int posY, bool debug);
void AddToCaptured(char* chessPiece, char* captured[16]);

// Piece placement
void PlacePawns(char* board[8][8], int bonusIterations[4], char* captured[16], bool debug);
void PlaceRooks(char* board[8][8], int extraRooks, char* captured[16], bool debug);
void PlaceBishops(char* board[8][8], int extraBishops, char* captured[16], bool debug);
void PlaceKnights(char* board[8][8], int extraKnights, char* captured[16], bool debug);
void PlaceQueens(char* board[8][8], int extraQueens, char* captured[16], bool debug);
void PlaceKing(char* board[8][8], bool debug);
void ShiftPawns(char* board[8][8], char* captured[16], bool debug);

// Text Output
void CheckMessage(char* checkingPiece, int posX, int posY, int kingX, int kingY);
void PlacementMessage(char* placedPiece1, char* placedPiece2, int posX, int posY);
char* SwapPiece(char* chessPiece);

#endif