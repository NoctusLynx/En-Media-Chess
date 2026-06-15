#ifndef BOARD_ASSESSMENT
#define BOARD_ASSESSMENT

// Utility Functions
char* ChessPiece(char code[3]);
bool IsOnBoard(int input);
bool SpaceOccupied(char* boardSpace);
void AddToCaptured(char* chessPiece, char* captured[16]);
int ScanPawnCodes(int key, int pawnCodes[8]);

// Printing Functions
void CheckMessage(char* checkingPiece, int checkRank, int checkFile, int kingRank, int kingFile);
char* SwapPiece(char* chessPiece);
void PlacementMessage(char* placedPiece1, int rank, int file);
char InvChessPiece(char* chessPiece);
void OutputFEN(char* board[8][8]);

#endif