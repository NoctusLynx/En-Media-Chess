// References
#pragma region
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

void PrintGreeting(void);    
void GenerateBoard(void);
void PrintBoard(char* board[8][8]);
void PrintLine(void);
void InitializeBoard(char* board[8][8]);
char ToUpperCase(char letter);
bool SpaceOccupied(char* boardSpace);
void PlacePawns(char* board[8][8], int bonusIterations[4]);
void PlaceRooks(char* board[8][8], int extraRooks);
void PlaceBishops(char* board[8][8], int extraBishops);
void PlaceKnights(char* board[8][8], int extraKnights);
void PlaceQueens(char* board[8][8], int extraQueens);
void PlaceKing(char* board[8][8]);
bool Check(char* board[8][8], int posX, int posY);
char* GetChessCharacter(char code[3]);
#pragma endregion

// Main and Ultilities
#pragma region
int main(void)
{
    setlocale(LC_ALL, "");
    puts("No issues w set locale");
    
    PrintGreeting();

    srand(time(NULL));

    int input = -1;
    scanf("%d", &input);
    switch(input)
    {
        // Generates the board
        case 1:
        GenerateBoard();
        
        // Exits the program via user input
        case 2:
        printf("Exiting...\n\n");
        break;
        
        // Exits the program via input error
        default:
        printf("ERROR: INPUT %d COULD NOT BE INTERPRETED, WILL EXIT PROGRAM NOW\n\n", input);
        break;
    }

    return 0;
}

void PrintGreeting(void)
{
    printf("Hello!\n\n");
    printf("Welcome to \"In Media Chess,\" a random board generator for more interesting chess games!\n\n");
    printf("Please select one of the options below:\n");
    printf("1: Generate Board\n");
    printf("2: Exit Program");
    printf("\n\n");
}

void PrintLine(void)
{
    printf("  -------------------\n");
}

char ToUpperCase(char letter)
{
    puts("Entered ToUpperCase()");
    switch(letter)
    {
        case 'a':   
        case 'A':   
        return 'A';

        case 'b':   
        puts("Black");
        case 'B':   
        return 'B';

        case 'c':   
        return 'C';

        case 'd':   
        return 'D';

        case 'e':   
        return 'E';

        case 'f':   
        return 'F';

        case 'g':   
        return 'G';

        case 'h':   
        return 'H';

        case 'i':   
        return 'I';

        case 'j':   
        return 'J';

        case 'k':   
        return 'K';

        case 'l':   
        return 'L';

        case 'm':   
        return 'M';

        case 'n':   
        return 'N';

        case 'o':   
        return 'O';

        case 'p':   
        return 'P';

        case 'q':   
        return 'Q';

        case 'r':   
        return 'R';

        case 's':   
        return 'S';

        case 't':   
        return 'T';

        case 'u':   
        return 'U';

        case 'v':   
        return 'V';

        case 'w':  
        case 'W': 
        puts("Ouput W");
        return 'W';

        case 'x':   
        return 'X';

        case 'y':   
        return 'Y';

        case 'z':   
        return 'Z';

        default:
        printf("Kept letter %c", letter);
        return letter;
    }
}

void GenerateBoard(void)
{
    char* board[8][8];
    int bonusIterations[4] = {0, 0, 0, 0};
    InitializeBoard(board);
    
    /*
    Generation notes:
    1. No more than 16 pieces for each player
    2. No more than 8 pawns
    3. Pawn has 20% chance, each, to not exist, 5% chance to be promoted to a different piece
    4. All other pieces (except King) have a 10% chance to not exist
    */
    
    // Place Pawns (8 ct, not on first or final row)
    puts("Adding pawns...");
    PlacePawns(board, bonusIterations);
    puts("Done.");

    // Note: Bonus iterations are in order as listed here

    // Place Rooks (2 ct, place anywhere)
    puts("Adding rooks...");
    PlaceRooks(board, bonusIterations[0]);
    puts("Done.");

    // Place Bishops (2ct: one on Dark Square, one on Light square)
    puts("Adding bishops...");
    PlaceBishops(board, bonusIterations[1]);
    puts("Done.");

    // Place Knights (2 ct, place anywhere)
    puts("Adding knights...");
    PlaceKnights(board, bonusIterations[2]);
    puts("Done.");

    // Place Queens (1 ct, anywhere)
    puts("Adding queens...");
    PlaceQueens(board, bonusIterations[3]);
    puts("Done.");

    // Place Kings (1 ct, re-run if check)
    puts("Adding kings...");
    PlaceKing(board);
    puts("Board generation complete, printing board:");

    PrintBoard(board);
    
    printf("\n\n");
}

void InitializeBoard(char* board[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            board[i][j] = ".";
        }
    }
}

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
        case 'W':
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
        case 'B':
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

bool SpaceOccupied(char* boardSpace)
{
    // strcmp returns 0 (false) when the two strings are the same
    if(!strcmp(boardSpace, "."))
        return false;
    else
        return true;
}
#pragma endregion

// Graphical Output and Piece Placement
#pragma region
void PrintBoard(char* board[8][8])
{
    PrintLine();

    for(int i = 0; i < 8; i++)
    {
        // Prints row header
        printf("%d | ", 8 - i);
        
        for(int j = 0; j < 8; j++)
        {
            printf("%s ", board[i][j]);
        }

        printf("|\n");

    }

    PrintLine();
}

void PlacePawns(char* board[8][8], int bonusIterations[4])
{
    // Iterates 8 times, one for each possible pawn
    for(int i = 0; i < 8; i++)
    {
        // Randomize values
        int rng = rand() % 10;

        // 10% chance to be promoted to different piece
        if(rng < 1)
        {
            puts("Bonus piece triggered:");
            rng = rand() % 4;

            switch(rng)
            {
                // Rook
                case 0:
                bonusIterations[0]++;
                puts("Extra Rook triggered.");
                break;

                // Knight
                case 1:
                bonusIterations[1]++;
                puts("Extra Knight triggered.");
                break;

                // Bishop
                case 2:
                bonusIterations[2]++;
                puts("Extra Bishop triggered.");
                break;

                // Queen
                case 3:
                bonusIterations[3]++;
                puts("Extra Queen triggered.");
                break;
            }
        }
        // 20% chance to not exist
        else if(rng < 3)
        {
            puts("rng < 3; No pawn created");
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
            
            printf("%s at %d%c\n", GetChessCharacter("BP"), rng + 1, (char)(i + 65));
            printf("%s at %d%c\n", GetChessCharacter("WP"), 7 - rng + 1, (char)(7 - i + 65));

            board[rng][i] = GetChessCharacter("BP");
            board[7 - rng][7 - i] = GetChessCharacter("WP");
        }

    }
}

void PlaceRooks(char* board[8][8], int extraRooks)
{
    for(int i = 0; i < 2 + extraRooks; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
            puts("1 set os rooks eliminated.");
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
            printf("%s at %d%c\n", GetChessCharacter("BR"), rng1 + 1, (char)(rng2 + 65));
            printf("%s at %d%c\n", GetChessCharacter("WR"), 7 - rng1 + 1, (char)(7 - rng2 + 65));
            
            board[rng1][rng2] = GetChessCharacter("BR");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WR");
        }
    }
}

void PlaceBishops(char* board[8][8], int extraBishops)
{
    for(int i = 0; i < 2 + extraBishops; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
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
            rng2++;
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
            printf("%s at %d%c\n", GetChessCharacter("BB"), rng1 + 1, (char)(rng2 + 65));
            printf("%s at %d%c\n", GetChessCharacter("WB"), 7 - rng1 + 1, (char)(7 - rng2 + 65));
            
            board[rng1][rng2] = GetChessCharacter("BB");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WB");
        }
    }
}

void PlaceKnights(char* board[8][8], int extraKnights)
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
            board[rng1][rng2] = GetChessCharacter("BN");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WN");
        }
    }
}

void PlaceQueens(char* board[8][8], int extraQueens)
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
            board[rng1][rng2] = GetChessCharacter("BQ");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WQ");
        }
    }
}

void PlaceKing(char* board[8][8])
{
    

    for(int i = 0; i < 1; i++)
    {
        int rng1 = rand() % 10;
        int rng2 = rand() % 10;

        if(SpaceOccupied(board[rng1][rng2]) || SpaceOccupied(board[7 - rng1][7 - rng2]) || Check(board, 7 - rng1, 7 - rng2))
        {
            i--;
            continue;
        }
        else
        {
            board[rng1][rng2] = GetChessCharacter("BK");
            board[7 - rng1][7 - rng2] = GetChessCharacter("WK");
            break;
        }

    }
}

bool Check(char* board[8][8], int posX, int posY)
{
    // return 0 = false;    king is not in check
    // return 1 = true;     king is in check

    
    if(board[posX][posY] == GetChessCharacter("WK"))
    {
        // Then, perform checks on the king to see if the king is in check or checkmate
        
        
        // Check if attacked by a Rook (or Queen)
        int n = posX + 1, m = posY;
        puts("Checking for check by rooks...");

        for(n; n < 8; n++)
        {
            if(!SpaceOccupied(board[n][m]))
                continue;

            else if(board[n][m] == GetChessCharacter("BR") || board[n][m] == GetChessCharacter("BQ"))
                return true;

            else if(SpaceOccupied(board[n][m]))
                break;
            
            else
                break;

        }

        n = posX - 1, m = posY;
        for(n; n >= 0; n--)
        {
            if(!SpaceOccupied(board[n][m]))
                continue;

            else if(board[n][m] == GetChessCharacter("BR") || board[n][m] == GetChessCharacter("BQ"))
                return true;

            else if(SpaceOccupied(board[n][m]))
                break;

            else 
                break;
        }

        n = posX, m = posY + 1;
        for(m ; m < 8; m++)
        {
            if(!SpaceOccupied(board[n][m]))
                continue;

            else if(board[n][m] == GetChessCharacter("BR") || board[n][m] == GetChessCharacter("BQ"))
                return true;

            else if(SpaceOccupied(board[n][m]))
                break;

            else
                break;
        }

        n = posX, m = posY - 1;
        for(m; m >= 0; m--)
        {
            if(!SpaceOccupied(board[n][m]))
                continue;

            else if(board[n][m] == GetChessCharacter("BR") || board[n][m] == GetChessCharacter("BQ"))
                return true;
            
            else if(SpaceOccupied(board[n][m]))
                break;

            else
                break;
        }
        puts("Done.");
        
        // Check if attacked by a Bishop (or Queen)
        n = posX, m = posY;
        puts("Checking for checks by bishops.");

        while(n < 8 && m < 8)
        {
            if(!SpaceOccupied(board[++n][++m]))
                continue;
            
            else if(board[n][m] == GetChessCharacter("BB") || board[n][m] == GetChessCharacter("BQ"))
                return true;
            
            else if(SpaceOccupied(board[n][m]))
                break;

            else
                break;

        }

        n = posX, m = posY;
        while(n >= 0 && m < 8)
        {
            if(!SpaceOccupied(board[--n][++m]))
                continue;

            else if(board[n][m] == GetChessCharacter("BB") || board[n][m] == GetChessCharacter("BQ"))
                return true;

            else if(SpaceOccupied(board[n][m]))
                break;
            
            else
                break;
        }

        n = posX, m = posY;
        while(n < 8 || m >= 0)
        {
            if(!SpaceOccupied(board[++n][--m]))
                continue;
            
            else if(board[n][m] == GetChessCharacter("BB") || board[n][m] == GetChessCharacter("BQ"))
                return true;
            
            else if(SpaceOccupied(board[n][m]))
                break;
            
            else    
                break;
        }

        n = posX, m = posY;
        while(n >= 0 || m >= 0)
        {
            if(SpaceOccupied(board[--n][--m]))
                continue;
            
            else if(board[n][m] == GetChessCharacter("BB") || board[n][m] == GetChessCharacter("BQ"))
                return true;
            
            else if(SpaceOccupied(board[n][m]))
                break;
            
            else    
                break;
        }
        puts("Done.");
        
        // Check if attacked by a Knight
        n = posX, m = posY;
        puts("Checking for checks by knights...");
        if(n + 2 < 8)
        {
            if(m + 1 < 8)
            {
                if(board[n + 2][m + 1] == GetChessCharacter("BN"))
                    return true;
            }
            
            if(m - 1 >= 0)
            {
                if(board[n + 2][m - 1] == GetChessCharacter("BN"))
                    return true;
            }
            
        }

        if(n - 2 >= 0)
        {
            if(m + 1 < 9)
            {
                if(board[n - 2][m + 1] == GetChessCharacter("BN"))
                    return true;
            }
            if(m - 1 >= 0)
            {
                if(board[n - 2][m - 1] == GetChessCharacter("BN"))
                    return true;
            }
        }
        
        if(n + 1 < 8)
        {
            if(m + 2 < 8)
            {
                if(board[n + 1][m + 2] == GetChessCharacter("BN"))
                    return true;
            }

            if(m - 2 >= 0)
            {
                if(board[n + 1][m - 2] == GetChessCharacter("BN"))
                    return true;
            }
        }

        if(n - 1 >= 0)
        {
            if(m + 2 < 8)
            {
                if(board[n - 1][m + 2] == GetChessCharacter("BN"))
                    return true;
            }

            if(m - 2 >= 0)
            {
                if(board[n - 1][m - 2] == GetChessCharacter("BN"))
                    return true;
            }
        }
        puts("Done.");

        // Check if attacked by a Pawn (or King)
        puts("Checking for checks by pawns or kings...");
        n = posX, m = posY;
        for(int a = -1; a <= 1; a++)
        {
            for(int b = -1; b <= 1; b++)
            {
                if(a == 0 && b == 0)
                    continue;
                
                if(a = -1 || b != 0)
                {
                    if(board[n + a][m + b] == GetChessCharacter("BP"))
                        return true;;
                }

                if(board[n + a][m + b] == GetChessCharacter("BK"))
                    return true;
            }
        }
        puts("Done.");
        puts("No checks found!");
        // If all checks fail, return false
        return false;
    }
    else
    {
        puts("ERROR: King not found in indicated position!");
        return true;
    }
        
    
    
    return 0;
}
#pragma endregion