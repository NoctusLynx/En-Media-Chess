// Refences
#pragma region

#include "ChessUtilities.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma endregion

// Board Assessment
#pragma region

char* ChessPiece(char code[3])
{
    // code[0] = team
    // code[1] = piece
    //puts("Before uppcercase");
    // Force inputs to lower case
    //code[0] = ToUpperCase(code[0]);
    //puts("After first uppercase");
    //code[1] = ToUpperCase(code[1]);
    //puts("After second uppercase");

    switch(code[0])
    {
        // Black Pieces
        case 'B':
        switch(code[1])
        {
            // Black King
            case 'K':   return "\u265A";
            
            // Black Queen
            case 'Q':   return "\u265B";

            // Black Rook
            case 'R':   return "\u265C";

            // Black Bishop
            case 'B':   return "\u265D";
            
            // Black Knight
            case 'N':   return "\u265E";

            // Black Pawn
            case 'P':   return "\u265F";

            // Black Space
            case 'S':   return "\u25AA";
        }
        break;

        // White Pieces
        case 'W':
        switch(code[1])
        {
            // White King
            case 'K':   return "\u2654";
    
            // White Queen
            case 'Q':   return "\u2655";
    
            // White Rook
            case 'R':   return "\u2656";
    
            // White Bishop
            case 'B':   return "\u2657";
            
            // White Knight
            case 'N':   return "\u2658";
            
            // White Pawn
            case 'P':   return "\u2659";

            // White Space
            case 'S':   return "\u25AB";
        }
        break;
    }

    return ".";
}

bool IsOnBoard(int input)
{
    if(input <= 7 && input >= 0)
        return true;
    
    else
        return false;
}

bool SpaceOccupied(char* boardSpace)
{
    // strcmp returns 0 (false) when the two strings are the same
    if(!strcmp(boardSpace, ChessPiece("BS")) || !strcmp(boardSpace, ChessPiece("WS")) || ! strcmp(boardSpace, ".") || !strcmp(boardSpace, " "))
        return false;
    else
        return true;
}

bool Check(char* board[8][8], int posX, int posY, bool debug)
{
    // return false =>  king is not in check
    // return true  =>  king is in check

    int n = 0, m = 0;

    debug ? printf("\tSpace available!\n\tScanning for check if %s  => %d%c...\n\n", ChessPiece("WK"), 7 - posX + 1, (char)(posY + 65)) : (void)0;
    
    // Then, perform checks on the king to see if the king is in check or checkmate
    
    // Check if attacked by a Rook (or Queen)
    if(true)
    {
        debug ?  puts("Scanning for check by Rooks or Queens...") : (void)0;
        
        int n = posX, m = posY;
    
        while(IsOnBoard(++n) && IsOnBoard(m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
    
            else if(!strcmp(board[n][m], ChessPiece("BR")))
            {
                debug ? CheckMessage(ChessPiece("BR"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
                
                return true;
            }    
    
            else if(SpaceOccupied(board[n][m]))
                break;
            
            else
                break;
    
        }
    
        n = posX - 1, m = posY;
        while(IsOnBoard(--n) && IsOnBoard(m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
    
            else if(!strcmp(board[n][m], ChessPiece("BR")))
            {
                debug ? CheckMessage(ChessPiece("BR"), n, m, posX, posY) : (void)0;
    
                return true;
            }  
            
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
    
            else if(SpaceOccupied(board[n][m]))
                break;
    
            else 
                break;
        }
    
        n = posX, m = posY + 1;
        while(IsOnBoard(n) && IsOnBoard(++m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
    
            else if(!strcmp(board[n][m], ChessPiece("BR")))
            {
                debug ? CheckMessage(ChessPiece("BR"), n, m, posX, posY) : (void)0;
                
                return true;
            }
    
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
    
            else if(SpaceOccupied(board[n][m]))
                break;
    
            else
                break;
        }
    
        n = posX, m = posY - 1;
        while(IsOnBoard(n) && IsOnBoard(--m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
    
            else if(!strcmp(board[n][m], ChessPiece("BR")))
            {
                debug ? CheckMessage(ChessPiece("BR"), n, m, posX, posY) : (void)0;
                
                return true;
            }
            
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            
            else if(SpaceOccupied(board[n][m]))
                break;
    
            else
                break;
        }
        
        debug ? puts("\tDone.\n") : (void)0;
    }
    
    // Check if attacked by a Bishop (or Queen)
    if(true)
    {
        debug ? puts("Scanning for checks by Bishops or Queens...")  : (void)0;
        
        n = posX, m = posY;
    
        while(IsOnBoard(++n) && IsOnBoard(++m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
            
            else if(!strcmp(board[n][m], ChessPiece("BB")))
            {
                debug ? CheckMessage(ChessPiece("BB"), n, m, posX, posY)  : (void)0;
    
                return true;
            }
    
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            
            else if(SpaceOccupied(board[n][m]))
                break;
    
            else
                break;
    
        }
    
        n = posX, m = posY;
        while(IsOnBoard(--n) && IsOnBoard(++m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
    
            else if(!strcmp(board[n][m], ChessPiece("BB")))
            {
                debug ? CheckMessage(ChessPiece("BB"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
    
            else if(SpaceOccupied(board[n][m]))
                break;
            
            else
                break;
        }
    
        n = posX, m = posY;
        while(IsOnBoard(++n) && IsOnBoard(--m))
        {
            if(!SpaceOccupied(board[n][m]))
                continue;
            
            else if(!strcmp(board[n][m], ChessPiece("BB")))
            {
                debug ? CheckMessage(ChessPiece("BB"), n, m, posX, posY) : (void)0;
    
                return true;
            }
    
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            
            else if(SpaceOccupied(board[n][m]))
                break;
            
            else    
                break;
        }
    
        n = posX, m = posY;
        while(IsOnBoard(--n) && IsOnBoard(--m))
        {
            if(SpaceOccupied(board[n][m]))
                continue;
            
            else if(!strcmp(board[n][m], ChessPiece("BB")))
            {
                debug ? CheckMessage(ChessPiece("BB"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            else if(!strcmp(board[n][m], ChessPiece("BQ")))
            {
                debug ? CheckMessage(ChessPiece("BQ"), n, m, posX, posY) : (void)0;
    
                return true;
            }
            
            else if(SpaceOccupied(board[n][m]))
                break;
            
            else    
                break;
        }
        
        debug ? puts("\tDone.\n") : (void)0;   
    }
    
    // Check if attacked by a Knight
    if(true)
    {
        debug ? puts("Scanning for checks by Knights...") : (void)0;
        
        n = posX, m = posY;
        
        if(IsOnBoard(n + 2))
        {
            if(IsOnBoard(m + 1))
            {
                if(!strcmp(board[n + 2][m + 1], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n + 2, m + 1, posX, posY) : (void)0;
    
                    return true;
                }
            }
            
            if(IsOnBoard(m - 1))
            {
                if(!strcmp(board[n + 2][m - 1], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n + 2, m - 1, posX, posY) : (void)0;
    
                    return true;
                }
            }
            
        }
    
        if(IsOnBoard(n- 2))
        {
            if(IsOnBoard(m + 1))
            {
                if(!strcmp(board[n - 2][m + 1], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n - 2, m + 1, posX, posY) : (void)0;
    
                    return true;
                }
            }
            if(IsOnBoard(m- 1))
            {
                if(!strcmp(board[n - 2][m - 1], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n - 2 , m - 1, posX, posY) : (void)0;
    
                    return true;
                }
            }
        }
        
        if(IsOnBoard(n + 1))
        {
            if(IsOnBoard(m + 2))
            {
                if(!strcmp(board[n + 1][m + 2], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n + 1, m + 2, posX, posY) : (void)0;
    
                    return true;
                }
            }
    
            if(IsOnBoard(m - 2))
            {
                if(!strcmp(board[n + 1][m - 2], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n + 1, m - 2, posX, posY) : (void)0;
    
                    return true;
                }
            }
        }
    
        if(IsOnBoard(n - 1))
        {
            if(IsOnBoard(m + 2))
            {
                if(!strcmp(board[n - 1][m + 2], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n - 1, m + 2, posX, posY) : (void)0;
    
                    return true;
                }
            }
    
            if(IsOnBoard(m - 2))
            {
                if(!strcmp(board[n - 1][m - 2], ChessPiece("BN")))
                {
                    debug ? CheckMessage(ChessPiece("BN"), n - 1, m - 2, posX, posY) : (void)0;
    
                    return true;
                }
            }
        }
        
        debug ? puts("\tDone.\n") : (void)0;
    }

    // Check if attacked by a Pawn (or King)
    if(true)
    {
        debug ? puts("Scanning for checks by Pawns or Kings...") : (void)0;
        
        n = posX, m = posY;
        
        for(int a = -1; a <= 1; a++)
        {
            for(int b = -1; b <= 1; b++)
            {
                if(a == 0 && b == 0)
                    continue;
                
                if(!IsOnBoard(n + a) || !IsOnBoard(m + b))
                    continue;
    
                if(a == -1 || b != 0)
                {
                    if(!strcmp(board[n + a][m + b], ChessPiece("BP")))
                    {
                        debug ? CheckMessage(ChessPiece("BP"), n, m, posX, posY) : (void)0;
    
                        return true;
                    }
                }
    
                if(!strcmp(board[n + a][m + b], ChessPiece("BK")))
                {
                    debug ? CheckMessage(ChessPiece("BK"), n, m, posX, posY) : (void)0;
    
                    return true;
                }
            }
        }
        
        debug ? puts("\tDone.\n") : (void)0;
    }

    debug ? puts("No checks found!") : (void)0;
    
    // If all checks fail, return false
    return false;
}

void AddToCaptured(char* chessPiece, char* captured[16])
{
    for(int i = 0; i < 16; i++)
    {
        if(!strcmp("", captured[i]))
        {
            captured[i] = chessPiece;
            break;
        }
        else
        {
            continue;
        }
    }
}

#pragma endregion

// Piece Placement
#pragma region

void PlacePawns(char* board[8][8], int bonusIterations[4], char* captured[16], bool debug)
{
    // Iterates 8 times, one for each possible pawn
    for(int i = 0; i < 8; i++)
    {
        // Randomize values
        int rng = rand() % 10;

        // 10% chance to be promoted to different piece
        if(rng < 1)
        {
            debug ? printf("\t( %s , %s ) => ", ChessPiece("BP"), ChessPiece("WP")) : (void)0;
            rng = rand() % 4;

            switch(rng)
            {
                // Rook
                case 0:

                bonusIterations[0]++;
                debug ? printf("( %s  , %s  )\n", ChessPiece("BR"), ChessPiece("WR")) : (void)0;
                
                break;

                // Knight
                case 1:

                bonusIterations[1]++;
                debug ? printf("( %s  , %s  )\n", ChessPiece("BN"), ChessPiece("WN")) : (void)0;
                
                break;

                // Bishop
                case 2:

                bonusIterations[2]++;
                debug ? printf("( %s  , %s  )\n", ChessPiece("BB"), ChessPiece("WB")) : (void)0;

                break;

                // Queen
                case 3:
                
                bonusIterations[3]++;
                debug ? printf("( %s  , %s  )\n", ChessPiece("BQ"), ChessPiece("WQ")) : (void)0;
                
                break;
            }
        }
        // 20% chance to not exist
        else if(rng < 3)
        {
            debug ? printf("\t( %s , %s ) => ( X  , X  )\n", ChessPiece("BP"), ChessPiece("WP"))  : (void)0;
            AddToCaptured(ChessPiece("WP"), captured);
            continue;
        }
        else
        {
            // Selects a spot on the column
            rng = rand() % 3 + 1;
            
            // Checks if that space is available
            if(SpaceOccupied(board[rng][i]) || SpaceOccupied(board[7 - rng][7 - i]))
            {
                i--;

                continue;
            }    
            
            if(debug) 
            {
                PlacementMessage(ChessPiece("BP"), ChessPiece("WP"), rng, i);
            }

            board[rng][i] = ChessPiece("BP");
            board[7 - rng][7 - i] = ChessPiece("WP");
        }

    }
}

void PlaceRooks(char* board[8][8], int extraRooks, char* captured[16], bool debug)
{
    debug ? printf("\tTotal %s : 2 + %d = %d\n", ChessPiece("WR"), extraRooks, 2 + extraRooks) : (void)0;
    
    for(int i = 0; i < 2 + extraRooks; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
            debug ? printf("\t( %s , %s ) => ( X  , X  )\n", ChessPiece("BR"), ChessPiece("WR")) : (void)0;
            AddToCaptured(ChessPiece("WR"), captured);
            continue;
        }
            

        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][7 - rng2]))
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            if(debug) 
            {
                PlacementMessage(ChessPiece("BR"), ChessPiece("WR"), rng1, rng2);
            }
            
            board[rng1][rng2] = ChessPiece("BR");
            board[7 - rng1][7 - rng2] = ChessPiece("WR");
        }
    }
}

void PlaceBishops(char* board[8][8], int extraBishops, char* captured[16], bool debug)
{
    debug ? printf("\tTotal %s : 2 + %d = %d\n", ChessPiece("WB"), extraBishops, 2 + extraBishops) : (void)0;
    
    for(int i = 0; i < 2 + extraBishops; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
            debug ? printf("\t( %s , %s ) => ( X  , X  )\n", ChessPiece("BB"), ChessPiece("WB")) : (void)0;
            AddToCaptured(ChessPiece("WB"), captured);
            continue;
        }
            
        // 50% chance to be a light or dark square bishop
        coin = rand() % 2;

        // Guarantees that the first two bishops are on opposite colored squares for fairness
        if(i == 0)
            coin = 0;

        else if(i == 1)
            coin = 1;

        int rng1 = 2 * (rand() % 4);
        int rng2 = 2 * (rand() % 4);

        // If coin is even, then both rng values are even; if coid is odd, both rng values are odd
        if(coin == 1)
        {
            rng1++;
            if(rng1 >= 8)
                rng1 = 0;
        }

        if(!IsOnBoard(!rng1) || ! IsOnBoard(rng2))
        {
            i--;
            continue;
        }

        // If the space is occupied, re-roll position
        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][7 - rng2]))
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            if(debug) 
            {
                PlacementMessage(ChessPiece("BB"), ChessPiece("WB"), rng1, rng2);
            }
            
            board[rng1][rng2] = ChessPiece("BB");
            board[7 - rng1][7 - rng2] = ChessPiece("WB");
        }
    }
}

void PlaceKnights(char* board[8][8], int extraKnights, char* captured[16], bool debug)
{
    debug ? printf("\tTotal %s: 2 + %d = %d\n", ChessPiece("WN"), extraKnights, 2 + extraKnights) : (void)0;
    
    for(int i = 0; i < 2 + extraKnights; i ++)
    {
        int coin = rand() % 10;
        
        if(coin < 1)
        {
            debug ? printf("\t( %s , %s ) => ( X  , X  )\n", ChessPiece("BN"), ChessPiece("WN")) : (void)0;
            AddToCaptured(ChessPiece("WN"), captured);
            continue;
        }

        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][ 7- rng2]))
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            if(debug) 
            {
                PlacementMessage(ChessPiece("BN"), ChessPiece("WN"), rng1, rng2);
            }
            
            board[rng1][rng2] = ChessPiece("BN");
            board[7 - rng1][7 - rng2] = ChessPiece("WN");
        }
    }
}

void PlaceQueens(char* board[8][8], int extraQueens, char* captured[16], bool debug)
{
    debug ? printf("\tTotal %s: 2 + %d = %d\n", ChessPiece("WQ"), extraQueens, 2 + extraQueens) : (void)0;

    for(int i = 0; i < 1 + extraQueens; i ++)
    {
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        int coin = rand() % 10;

        if(coin < 1)
        {
            debug ? printf("\t( %s ,  %s ) => ( X  , X  )\n", ChessPiece("BQ"), ChessPiece("WQ")) : (void)0;
            AddToCaptured(ChessPiece("WQ"), captured);
        }

        // If the space is occupied, re-roll position
        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][7 - rng2]))
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            if(debug) 
            {
                PlacementMessage(ChessPiece("BQ"), ChessPiece("WQ"), rng1, rng2);
            }
            
            board[rng1][rng2] = ChessPiece("BQ");
            board[7 - rng1][7 - rng2] = ChessPiece("WQ");
        }
    }
}

void PlaceKing(char* board[8][8], bool debug)
{
    

    for(int i = 0; i < 1; i++)
    {
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        if(debug) 
        {
            printf("( %s , %s ) <=> ( %d%c , %d%c )\n", 
                board[rng1][rng2], board[7 - rng1][7 - rng2], 7 - rng1 + 1, 
                (char)(rng2 + 65), rng1 + 1, (char)(7 - rng2 + 65));
        }
        

        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][7 - rng2]) || Check(board, 7 - rng1, 7 - rng2, debug))
        {
            debug ? puts("\tInvalid location, re-rolling king placement.\n") : (void)0;
            i--;
            continue;
        }
        else
        {
            debug ? PlacementMessage(ChessPiece("BK"), ChessPiece("WK"), rng1, rng2) : (void)0;
            
            board[rng1][rng2] = ChessPiece("BK");
            board[7 - rng1][7 - rng2] = ChessPiece("WK");
        }

    }
}

void ShiftPawns(char* board[8][8], char* captured[16], bool debug)
{
    // Count the number of captured pieces
    int numCaptured = 0;
    for(int i = 0; i < 16; i++)
    {
        if(!strcmp(captured[i], ""))
            break;

        else
            numCaptured++;
    }

    // If no pieces were captured, dorce quit the function
    if(numCaptured <= 0)
        return;

    debug ? printf("\tNumber of captured pieces: %d\n", numCaptured) : (void)0;

    int threshold = 5;

    // Parse the board for pawns
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            // Fires if a pawn is found
            if(!strcmp(board[i][j], ChessPiece("WP")) || !strcmp(board[i][j], ChessPiece("BP")))
            {
                
                // Select a horizontal direction at random
                int horizontal = 2 * (rand() % 2) - 1;
                
                // Select a vertical direction based on the type of the found pawn
                int vertical = !strcmp(board[i][j], ChessPiece("WP")) ? -1 : 1;

                // Check that the new locations are within the bounds of the board
                if(!IsOnBoard(i + vertical) || !IsOnBoard(j + horizontal) || !IsOnBoard(7 - i - vertical) || !IsOnBoard(7 - j - horizontal))
                {   
                    // If it isn't, flip the direction of the horizontal change, and try again
                    horizontal *= -1;
                    
                    // If it's still off the board
                    if(!IsOnBoard(j + horizontal) || !IsOnBoard(7 - j - horizontal))
                    {
                        // Skip it
                        continue;
                    }
                }

                // Check if space or its complement is available
                if(!SpaceOccupied(board[i + vertical][j + horizontal]) || !SpaceOccupied(board[7 - i - vertical][7 - j - horizontal]))
                {
                    
                    if(( rand() % 10 ) < threshold)
                    {
                        
                        debug ? 
                            printf("\t( %s  , %s  ) => ( %d%c, %d%c ) => ( %d%c, %d%c)\n", 
                            board[i][j], board[7 - i][7 - j], 
                            7 - i + 1, (char)(j + 65), i + 1, (char)(7 - j + 65), 
                            7 - i + 1 - vertical, (char)(j + horizontal + 65), i + 1 + vertical, (char)(7 - j - horizontal + 65)) :
                            (void)0;
                        
                        // Resets the threshold amount
                        threshold = 5;

                        // Add pawns to new locations
                        board[i + vertical][j + horizontal] = !strcmp(board[i][j], ChessPiece("WS")) ? ChessPiece("WS") : ChessPiece("BP");
                        board[7 - i - vertical][7 - j - horizontal] = !strcmp(board[7 - i][7 - j], ChessPiece("WP")) ? ChessPiece("WP") : ChessPiece("BP");
    
                        // Remove pawns from current locations (replace with appropriate colored tile)
                        // Light = sum of coordinates is even;  (i + j) % 2 = 0 = false
                        // Dark = sum of coordinates is odd;    (i + j) % 2 = 1 = true
                        board[i][j] = ((i + j) % 2) ? ChessPiece("BS") : ChessPiece("WS");
                        board[7 - i][7 - j] = ((14 - i - j) % 2) ? ChessPiece("BS") : ChessPiece("WS");
                    
                    }
                    else
                    {
                        debug ? printf("\tPawn shift skipped.\n") :  (void)0;
                        threshold++;
                    }
                    
                    // If the funtion has run out of iterations, force quit the function
                    if(--numCaptured <= 0)
                        return;
                    else
                        continue;
                    
                }
                
                else
                {
                    continue;
                }
                    
                     

            }
            
            // Skips if no pawn
            else
            {
                continue;
            }
        }

        // Loops back through the board until the function runs out of iterations
        if(i == 7)
        {
            debug ? puts("\tFull board scan complete, but iterations remain- resetting loop...") : (void)0;
            i = -1;
        }    

    }


}

#pragma endregion

// Text Outputs
#pragma region

void CheckMessage(char* checkingPiece, int checkX, int checkY, int kingX, int kingY)
{
    printf("\t%s at %d%c checks %s at %d%c\n", checkingPiece, 7 - checkX + 1, (char)(checkY + 65), ChessPiece("WK"), 7 - kingX + 1, (char)(kingY + 65));
}

void PlacementMessage(char* placedPiece1, char* placedPiece2, int posX, int posY)
{
    printf("\t( %s , %s ) => ( %d%c , %d%c )\n", placedPiece1, placedPiece2, 7 - posX + 1, (char)(posY + 65), 7 - (7 - posX) + 1, (char)(7 - posY + 65));
}

char* SwapPiece(char* chessPiece)
{
    // Pawns
    if(!strcmp(chessPiece, ChessPiece("BP")))
        return ChessPiece("WP");
    else if(!strcmp(chessPiece, ChessPiece("WP")))
        return ChessPiece("BP");
    
    // Rooks
    else if(!strcmp(chessPiece, ChessPiece("BR")))
        return ChessPiece("WR");
    else if(!strcmp(chessPiece, ChessPiece("WR")))
        return ChessPiece("BR");
    
    // Knights
    else if(!strcmp(chessPiece, ChessPiece("WN")))
        return ChessPiece("BN");
    else if(!strcmp(chessPiece, ChessPiece("BN")))
        return ChessPiece("WN");
    
    // Bishops
    else if(!strcmp(chessPiece, ChessPiece("WB")))
        return ChessPiece("BB");
    else if(!strcmp(chessPiece, ChessPiece("BB")))
        return ChessPiece("WB");

    // Queens
    else if(!strcmp(chessPiece, ChessPiece("WQ")))
        return ChessPiece("BQ");
    else if(!strcmp(chessPiece, ChessPiece("BQ")))
        return ChessPiece("WQ");

    // Kings
    else if(!strcmp(chessPiece, ChessPiece("WK")))
        return ChessPiece("BK");
    else if(!strcmp(chessPiece, ChessPiece("BK")))
        return ChessPiece("WK");
}

#pragma endregion