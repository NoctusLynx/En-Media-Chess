// References
#pragma region
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void PrintGreeting(void);    
void GenerateBoard(void);
void PrintBoard(char whiteBoard[8][8], char blackBoard[8][8]);
void PrintLine(void);
void InitializeBoards(char WhiteBoard[8][8], char BlackBoard[8][8]);
char ToLowerCase(char letter);
bool SpaceEmpty(char WhiteBoard[8][8], char blackBoard[8][8]);
void PlacePawns(char whiteBoard[8][8], char blackBoard[8][8], int bonusIterations[4]);
void PlaceRooks(char whiteBoard[8][8], char blackBoard[8][8], int extraRooks);
void PlaceBishops(char whiteBoard[8][8], char blackBoard[8][8], int extraBishops);
void PlaceKnights(char whiteBoard[8][8], char blackBoard[8][8], int extraKnights);
void PlaceQueens(char whiteBoard[8][8], char blackBoard[8][8], int extraQueens);
void PlaceKing(char whiteBoard[8][8], char blackBoard[8][8]);
bool Check(char whiteBoard[8][8], char blackBoard[8][8], int posX, int posY);
#pragma endregion

// Main and Ultilities
#pragma region
int main(void)
{
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

char ToLowerCase(char letter)
{
    switch(letter)
    {
        case 'P':
        return 'p';

        case 'R':
        return 'r';

        case 'B':
        return 'b';

        case 'N':
        return 'n';

        case 'K':
        return 'k';

        case 'Q':
        return 'q';
    }
}

void GenerateBoard(void)
{
    char whiteBoard[8][8];
    char blackBoard[8][8];
    int bonusIterations[4] = {0, 0, 0, 0};
    InitializeBoards(whiteBoard, blackBoard);

    /*
    Generation notes:
    1. No more than 16 pieces for each player
    2. No more than 8 pawns
    3. Pawn has 20% chance, each, to not exist, 5% chance to be promoted to a different piece
    4. All other pieces (except King) have a 10% chance to not exist
    */
    
    // Place Pawns (8 ct, not on first or final row)
    puts("Adding pawns...");
    PlacePawns(whiteBoard, blackBoard, bonusIterations);
    puts("Done.");

    // Note: Bonus iterations are in order as listed here

    // Place Rooks (2 ct, place anywhere)
    puts("Adding rooks...");
    PlaceRooks(whiteBoard, blackBoard, bonusIterations[0]);
    puts("Done.");

    // Place Bishops (2ct: one on Dark Square, one on Light square)
    puts("Adding bishops...");
    PlaceBishops(whiteBoard, blackBoard, bonusIterations[1]);
    puts("Done.");

    // Place Knights (2 ct, place anywhere)
    puts("Adding knights...");
    PlaceKnights(whiteBoard, blackBoard, bonusIterations[2]);
    puts("Done.");

    // Place Queens (1 ct, anywhere)
    puts("Adding queens...");
    PlaceQueens(whiteBoard, blackBoard, bonusIterations[3]);
    puts("Done.");

    // Place Kings (1 ct, re-run if check)
    puts("Adding kings...");
    PlaceKing(whiteBoard, blackBoard);
    puts("Board generation complete, printing board:");

    PrintBoard(whiteBoard, blackBoard);
    
    printf("\n\n");
}

void InitializeBoards(char whiteBoard[8][8], char blackBoard[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            whiteBoard[i][j] = '.';
            blackBoard[i][j] = '.';
        }
    }
}

bool SpaceEmpty(char whiteBoard[8][8], char blackBoard[8][8])
{
    
}
#pragma endregion

// Graphical Output and Piece Placement
#pragma region
void PrintBoard(char whiteBoard[8][8], char blackBoard[8][8])
{
    PrintLine();

    for(int i = 0; i < 8; i++)
    {
        // Prints row header
        printf("%d | ", 8 - i);
        
        for(int j = 0; j < 8; j++)
        {
            if(whiteBoard[i][j] != '.' && blackBoard[i][j] != '.')
            {
                printf("X ");
            }
            
            else if(whiteBoard[i][j] == '.' && blackBoard[i][j] == '.')
            {
                printf(". ");
            }

            else if(whiteBoard[i][j] == '.' && blackBoard[i][j] != '.')
            {
                printf("%c ", blackBoard[i][j]);
            }

            else if(whiteBoard[i][j] != '.' && blackBoard[i][j] == '.')
            {
                printf("%c ", whiteBoard[i][j]);
            }
            
        }

        printf("|\n");

    }

    PrintLine();
}

void PlacePawns(char whiteBoard[8][8], char blackBoard[8][8], int bonusIterations[4])
{
    // Iterates 8 times, one for each possible pawn
    for(int i = 0; i < 8; i++)
    {
        // Randomize values
        int rng = rand() % 10;

        // 10% chance to be promoted to different piece
        if(rng < 1)
        {
            rng = rand() % 4;

            switch(rng)
            {
                // Rook
                case 0:
                bonusIterations[0]++;
                break;

                // Knight
                case 1:
                bonusIterations[1]++;
                break;

                // Bishop
                case 2:
                bonusIterations[2]++;
                break;

                // Queen
                case 3:
                bonusIterations[3]++;
                break;
            }
        }
        
        // 20% chance to not exist
        else if(rng < 3)
        {
            continue;
        }
        
        else
        {
            // Selects a spot on the column
            rng = rand() % 6 + 1;
            
            // Checks if that space is available
            if(whiteBoard[rng][i] != '.' && blackBoard[rng][i] != '.')
            {
                i--;

                //printf("Duplicate found at (%d, %d)!\n\n", rng, i);

                continue;
            }    
            
            whiteBoard[rng][i] = 'P';
            blackBoard[7 - rng][7 - i] = 'p';
        }

    }
}

void PlaceRooks(char whiteBoard[8][8], char blackBoard[8][8], int extraRooks)
{
    for(int i = 0; i < 2 + extraRooks; i ++)
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if(coin < 1)
        {
            continue;
        }
            

        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[rng1][rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'R';
            blackBoard[7 - rng1][7 - rng2] = 'r';
        }
    }
}

void PlaceBishops(char whiteBoard[8][8], char blackBoard[8][8], int extraBishops)
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
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[rng1][rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'B';
            blackBoard[7 - rng1][7 - rng2] = 'b';
        }
    }
}

void PlaceKnights(char whiteBoard[8][8], char blackBoard[8][8], int extraKnights)
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
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[rng1][rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'N';
            blackBoard[7 - rng1][7 - rng2] = 'n';
        }
    }
}

void PlaceQueens(char whiteBoard[8][8], char blackBoard[8][8], int extraQueens)
{
    for(int i = 0; i < 1 + extraQueens; i ++)
    {
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[rng1][rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'Q';
            blackBoard[7 - rng1][7 - rng2] = 'q';
        }
    }
}

void PlaceKing(char whiteBoard[8][8], char blackBoard[8][8])
{
    

    for(int i = 0; i < 1; i++)
    {
        int rng1 = rand() % 10;
        int rng2 = rand() % 10;

        if(whiteBoard[rng1][rng2] != '.' || blackBoard[rng1][rng2] != '.' || Check(whiteBoard, blackBoard, rng1, rng2))
        {
            i--;
            continue;
        }
        else
        {
            whiteBoard[rng1][rng2] = 'K';
            blackBoard[7 - rng1][7 - rng2] = 'k';
            break;
        }

    }
}

bool Check(char whiteBoard[8][8], char blackBoard[8][8], int posX, int posY)
{
    // return 0 = false;    king is not in check
    // return 1 = true;     king is in check

    // First, look through the board...
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            // ...to find the king
            if(whiteBoard[i][j] == 'K')
            {
                // Then, perform checks on the king to see if the king is in check or checkmate
                
                
                // Check if attacked by a Rook (or Queen)
                int n = i + 1, m = j;
                puts("Checking for check by rooks...");

                for(n; n < 8; n++)
                {
                    if(blackBoard[n][m] == '.')
                        continue;

                    else if(blackBoard[n][m] == 'r' || blackBoard[n][m] == 'q')
                        return 1;

                    else if(whiteBoard[n][m] != '.')
                        break;
                    
                    else
                        break;

                }

                n = i - 1, m = j;
                for(n; n >= 0; n--)
                {
                    if(blackBoard[n][m] == '.')
                        continue;

                    else if(blackBoard[n][m] == 'r' || blackBoard[n][m] == 'q')
                        return 1;

                    else if(whiteBoard[n][m] != '.')
                        break;

                    else 
                        break;
                }

                n = i, m = j + 1;
                for(m ; m < 8; m++)
                {
                    if(whiteBoard[n][m] == '.')
                        continue;

                    else if(blackBoard[n][m] == 'r' || blackBoard[n][m] == 'q')
                        return 1;

                    else if(whiteBoard[n][m] != '.')
                        break;

                    else
                        break;
                }

                n = i, m = j - 1;
                for(m; m >= 0; m--)
                {
                    if(whiteBoard[n][m] == '.')
                        continue;

                    else if(blackBoard[n][m] == 'r' || blackBoard[n][m] == 'q')
                        return 1;
                    
                    else if(whiteBoard[n][m] != '.')
                        break;

                    else
                        break;
                }
                puts("Done.");
                
                // Check if attacked by a Bishop (or Queen)
                n = i, m = j;
                puts("Checking for checks by bishops.");

                while(n < 8 && m < 8)
                {
                    if(blackBoard[++n][++m] == '.')
                        continue;
                    
                    else if(blackBoard[n][m] == 'b' || blackBoard[n][m] == 'q')
                        return 1;
                    
                    else if(whiteBoard[n][m] != '.')
                        break;

                    else
                        break;

                }

                n = i, m = j;
                while(n >= 0 && m < 8)
                {
                    if(blackBoard[--n][++m] == '.')
                        continue;

                    else if(blackBoard[n][m] == 'b' || blackBoard[n][m] == 'q')
                        return 1;

                    else if(whiteBoard[n][m] != '.')
                        break;
                    
                    else
                        break;
                }

                n = i, m = j;
                while(n < 8 || m >= 0)
                {
                    if(blackBoard[++n][--m] == '.')
                        continue;
                    
                    else if(blackBoard[n][m] == 'b' || blackBoard[n][m] == 'q')
                        return 1;
                    
                    else if(whiteBoard[n][m] != '.')
                        break;
                    
                    else    
                        break;
                }

                n = i, m = j;
                while(n >= 0 || m >= 0)
                {
                    if(blackBoard[--n][--m] == '.')
                        continue;
                    
                    else if(blackBoard[n][m] == 'b' || blackBoard[n][m] == 'q')
                        return 1;
                    
                    else if(whiteBoard[n][m] != '.')
                        break;
                    
                    else    
                        break;
                }
                puts("Done.");
                
                // Check if attacked by a Knight
                n = i, m = j;
                puts("Checking for checks by knights...");
                if(n + 2 < 8)
                {
                    if(m + 1 < 8)
                    {
                        if(blackBoard[n + 2][m + 1] == 'n')
                            return 1;
                    }
                    
                    if(m - 1 >= 0)
                    {
                        if(blackBoard[n + 2][m - 1] == 'n')
                            return 1;
                    }
                    
                }

                if(n - 2 >= 0)
                {
                    if(m + 1 < 9)
                    {
                        if(blackBoard[n - 2][m + 1] == 'n')
                            return 1;
                    }
                    if(m - 1 >= 0)
                    {
                        if(blackBoard[n - 2][m - 1] == 'n')
                            return 1;
                    }
                }
                
                if(n + 1 < 8)
                {
                    if(m + 2 < 8)
                    {
                        if(blackBoard[n + 1][m + 2] == 'n')
                            return 1;
                    }

                    if(m - 2 >= 0)
                    {
                        if(blackBoard[n + 1][m - 2] == 'n')
                            return 1;
                    }
                }

                if(n - 1 >= 0)
                {
                    if(m + 2 < 8)
                    {
                        if(blackBoard[n - 1][m + 2] == 'n')
                            return 1;
                    }

                    if(m - 2 >= 0)
                    {
                        if(blackBoard[n - 1][m - 2] == 'n')
                            return 1;
                    }
                }
                puts("Done.");

                // Check if attacked by a Pawn (or King)
                puts("Checking for checks by pawns or kings...");
                n = i, m = j;
                for(int a = -1; a <= 1; a++)
                {
                    for(int b = -1; b <= 1; b++)
                    {
                        if(a == 0 && b == 0)
                            continue;
                        
                        if(a = -1 || b != 0)
                        {
                            if(blackBoard[n + a][m + b] == 'p')
                                return 1;
                        }

                        if(blackBoard[n + a][m + b] == 'k')
                            return 1;
                    }
                }
                puts("Done.");
                puts("No checks found!");
                // If all checks fail, return false
                return 0;
            }
        }
    }
    
    return 0;
}
#pragma endregion