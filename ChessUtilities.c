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

char* GetChessCharacter(char code[3])
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
        // White Pieces
        case 'B':
        switch(code[1])
        {
            // White King
            case 'K':   return "\u265A";
            
            // White Queen
            case 'Q':   return "\u265B";

            // White Rook
            case 'R':   return "\u265C";

            // White Bishop
            case 'B':   return "\u265D";
            
            // White Knight
            case 'N':   return "\u265E";

            // White Pawn
            case 'P':   return "\u265F";
        }
        break;

        // Black Pieces
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
    if(!strcmp(boardSpace, "."))
        return false;
    else
        return true;
}

bool Check(char* board[8][8], int posX, int posY, bool debug)
{
    // return 0 = false;    king is not in check
    // return 1 = true;     king is in check

    if(debug) printf("Checking for check if %s is at %d%c...\n", GetChessCharacter("WK"), 7 - posX + 1, (char)(posY + 65));
    
    // Then, perform checks on the king to see if the king is in check or checkmate
    
    
    // Check if attacked by a Rook (or Queen)
    int n = posX, m = posY;
    if(debug) puts("Checking for check by rooks...");

    while(IsOnBoard(++n) && IsOnBoard(m))
    {
        if(!SpaceOccupied(board[n][m]))
            continue;

        else if(board[n][m] == GetChessCharacter("BR"))
        {
            if(debug) CheckMessage(GetChessCharacter("BR"), n, m, posX, posY);

            return true;
        }
        
        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);
            
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

        else if(board[n][m] == GetChessCharacter("BR"))
        {
            if(debug) CheckMessage(GetChessCharacter("BR"), n, m, posX, posY);

            return true;
        }  
        
        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

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

        else if(board[n][m] == GetChessCharacter("BR"))
        {
            if(debug) CheckMessage(GetChessCharacter("BR"), n, m, posX, posY);
            
            return true;
        }

        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

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

        else if(board[n][m] == GetChessCharacter("BR"))
        {
            if(debug) CheckMessage(GetChessCharacter("BR"), n, m, posX, posY);
            
            return true;
        }
        
        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

            return true;
        }
        
        else if(SpaceOccupied(board[n][m]))
            break;

        else
            break;
    }
    if(debug) puts("Done.");
    
    // Check if attacked by a Bishop (or Queen)
    n = posX, m = posY;
    if(debug) puts("Checking for checks by bishops.");

    while(IsOnBoard(++n) && IsOnBoard(++m))
    {
        if(!SpaceOccupied(board[n][m]))
            continue;
        
        else if(board[n][m] == GetChessCharacter("BB"))
        {
            if(debug) CheckMessage(GetChessCharacter("BB"), n, m, posX, posY);

            return true;
        }

        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

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

        else if(board[n][m] == GetChessCharacter("BB"))
        {
            if(debug) CheckMessage(GetChessCharacter("BB"), n, m, posX, posY);

            return true;
        }
        
        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

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
        
        else if(board[n][m] == GetChessCharacter("BB"))
        {
            if(debug) CheckMessage(GetChessCharacter("BB"), n, m, posX, posY);

            return true;
        }

        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

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
        
        else if(board[n][m] == GetChessCharacter("BB"))
        {
            if(debug) CheckMessage(GetChessCharacter("BB"), n, m, posX, posY);

            return true;
        }
        else if(board[n][m] == GetChessCharacter("BQ"))
        {
            if(debug) CheckMessage(GetChessCharacter("BQ"), n, m, posX, posY);

            return true;
        }
        
        else if(SpaceOccupied(board[n][m]))
            break;
        
        else    
            break;
    }
    if(debug) puts("Done.");
    
    // Check if attacked by a Knight
    n = posX, m = posY;
    if(debug) puts("Checking for checks by knights...");
    if(IsOnBoard(n + 2))
    {
        if(IsOnBoard(m + 1))
        {
            if(board[n + 2][m + 1] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }
        
        if(IsOnBoard(m - 1))
        {
            if(board[n + 2][m - 1] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }
        
    }

    if(IsOnBoard(n- 2))
    {
        if(IsOnBoard(m + 1))
        {
            if(board[n - 2][m + 1] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }
        if(IsOnBoard(m- 1))
        {
            if(board[n - 2][m - 1] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }
    }
    
    if(IsOnBoard(n + 1))
    {
        if(IsOnBoard(m + 2))
        {
            if(board[n + 1][m + 2] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }

        if(IsOnBoard(m - 2))
        {
            if(board[n + 1][m - 2] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }
    }

    if(IsOnBoard(n - 1))
    {
        if(IsOnBoard(m + 2))
        {
            if(board[n - 1][m + 2] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }

        if(IsOnBoard(m - 2))
        {
            if(board[n - 1][m - 2] == GetChessCharacter("BN"))
            {
                if(debug) CheckMessage(GetChessCharacter("BN"), n, m, posX, posY);

                return true;
            }
        }
    }
    if(debug) puts("Done.");

    // Check if attacked by a Pawn (or King)
    if(debug) puts("Checking for checks by pawns or kings...");
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
                if(board[n + a][m + b] == GetChessCharacter("BP"))
                {
                    if(debug) CheckMessage(GetChessCharacter("BP"), n, m, posX, posY);

                    return true;
                }
            }

            if(board[n + a][m + b] == GetChessCharacter("BK"))
            {
                if(debug) CheckMessage(GetChessCharacter("BK"), n, m, posX, posY);

                return true;
            }
        }
    }
    if(debug) puts("Done.");
    if(debug) puts("No checks found!");
    // If all checks fail, return false
    return false;
}

#pragma endregion

// Piece Placement
#pragma region

void PlacePawns(char* board[8][8], int bonusIterations[4], bool debug)
{
    // Iterates 8 times, one for each possible pawn
    for(int i = 0; i < 8; i++)
    {
        // Randomize values
        int rng = rand() % 10;

        // 10% chance to be promoted to different piece
        if(rng < 1)
        {
            if(debug) puts("Bonus piece triggered:");
            rng = rand() % 4;

            switch(rng)
            {
                // Rook
                case 0:
                bonusIterations[0]++;
                if(debug) puts("Extra Rook triggered.");
                break;

                // Knight
                case 1:
                bonusIterations[1]++;
                if(debug) puts("Extra Knight triggered.");
                break;

                // Bishop
                case 2:
                bonusIterations[2]++;
                if(debug) puts("Extra Bishop triggered.");
                break;

                // Queen
                case 3:
                bonusIterations[3]++;
                if(debug) puts("Extra Queen triggered.");
                break;
            }
        }
        // 20% chance to not exist
        else if(rng < 3)
        {
            if(debug) puts("rng < 3; No pawn created");
            continue;
        }
        else
        {
            // Selects a spot on the column
            rng = rand() % 6 + 1;
            
            // Checks if that space is available
            if(SpaceOccupied(board[rng][i]) || SpaceOccupied(board[7 - rng][7 - i]))
            {
                i--;

                continue;
            }    
            
            if(debug) 
            {
                PlacementMessage(GetChessCharacter("BP"), rng, i);
                PlacementMessage(GetChessCharacter("WP"), 7 - rng, 7 - i);
            }

            board[rng][i] = GetChessCharacter("BP");
            board[7 - rng][7 - i] = GetChessCharacter("WP");
        }

    }
}

void PlaceRooks(char* board[8][8], int extraRooks, bool debug)
{
    for(int i = 0; i < 2 + extraRooks; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
            if(debug) puts("1 pair of Rooks eliminated.");
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
                PlacementMessage(GetChessCharacter("BR"), rng1, rng2);
                PlacementMessage(GetChessCharacter("WR"), 7 - rng1, 7 - rng2);
            }
            
            board[rng1][rng2] = GetChessCharacter("BR");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WR");
        }
    }
}

void PlaceBishops(char* board[8][8], int extraBishops, bool debug)
{
    for(int i = 0; i < 2 + extraBishops; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
            if(debug) puts("1 pair of Bishops eliminated.");
            continue;
        }
            
        // 50% chance to be a light or dark square bishop
        coin = rand() % 2;

        // Guarantees that the first two bishops are on opposite colored squares for fairness
        if(i == 0)
        {
            coin = 0;
        }
        else if(i == 1)
        {
            coin = 1;
        }

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
                PlacementMessage(GetChessCharacter("BB"), rng1, rng2);
                PlacementMessage(GetChessCharacter("WB"), 7 - rng1, 7 - rng2);
            }
            
            board[rng1][rng2] = GetChessCharacter("BB");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WB");
        }
    }
}

void PlaceKnights(char* board[8][8], int extraKnights, bool debug)
{
    for(int i = 0; i < 2 + extraKnights; i ++)
    {
        int coin = rand() % 10;
        
        if(coin < 1)
        {
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
                PlacementMessage(GetChessCharacter("BN"), rng1, rng2);
                PlacementMessage(GetChessCharacter("WN"), 7 - rng1, 7 - rng2);
            }
            
            board[rng1][rng2] = GetChessCharacter("BN");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WN");
        }
    }
}

void PlaceQueens(char* board[8][8], int extraQueens, bool debug)
{
    for(int i = 0; i < 1 + extraQueens; i ++)
    {
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
                PlacementMessage(GetChessCharacter("BQ"), rng1, rng2);
                PlacementMessage(GetChessCharacter("WQ"), 7 - rng1, 7 - rng2);
            }
            
            board[rng1][rng2] = GetChessCharacter("BQ");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WQ");
        }
    }
}

void PlaceKing(char* board[8][8], bool debug)
{
    

    for(int i = 0; i < 1; i++)
    {
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        if(debug) printf("%s is at %d%c\n", board[rng1][rng2], 7 - rng1 + 1, (char)(rng2 + 65));
        if(debug) printf("%s is at %d%c\n", board[7 - rng1][7 - rng2], rng1 + 1, (char)(7 - rng2 + 65));

        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][7 - rng2]) || Check(board, 7 - rng1, 7 - rng2, debug))
        {
            i--;
            continue;
        }
        else
        {
            if(debug) 
            {
                PlacementMessage(GetChessCharacter("BK"), rng1, rng2);
                PlacementMessage(GetChessCharacter("WK"), 7 - rng1, 7 - rng2);
            }
            
            board[rng1][rng2] = GetChessCharacter("BK");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WK");
        }

    }
}

#pragma endregion

// Text Outputs
#pragma region

void CheckMessage(char* checkingPiece, int checkX, int checkY, int kingX, int kingY)
{
    printf("%s at %d%c checks %s at %d%c\n", checkingPiece, 7 - checkX + 1, (char)(checkY + 65), GetChessCharacter("WK"), 7 - kingX + 1, (char)(kingY + 65));
}

void PlacementMessage(char* placedPiece, int posX, int posY)
{
    printf("%s placed at %d%c\n", placedPiece, 7 - posX + 1, (char)(posY + 65));
}

#pragma endregion