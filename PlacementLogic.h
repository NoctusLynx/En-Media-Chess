#ifndef PLACEMENT_LOGIC
#define PLACEMENT_LOGIC

#include <stdbool.h>

// Board Assessment



// Piece placement
void PlacePiece(char* board[8][8], char* chessPiece, int rank, int file, bool debug);
void PlacePawns(char* board[8][8], char* captured[16], int pawnCodes[8], bool debug);
void PlaceRooks(char* board[8][8], int extraRooks, char* captured[16], bool debug);
void PlaceBishops(char* board[8][8], int extraBishops, char* captured[16], int pawnCodes[8], int bishopCodes[10], bool debug);
void PlaceKnights(char* board[8][8], int extraKnights, char* captured[16], bool debug);
void PlaceQueens(char* board[8][8], int extraQueens, char* captured[16], bool debug);
void PlaceKing(char* board[8][8], bool debug);
bool Check(char* board[8][8], int posX, int posY, bool debug);
void ShiftPawns(char* board[8][8], char* captured[16], int pawnCodes[8], int bishopCodes[10], bool debug);

#endif