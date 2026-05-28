// References
#pragma region
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bool.h>

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
void Check(char whiteBoard[8][8], char blackBoard[8][8], int posX, int posY);
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
    PlacePawns(whiteBoard, blackBoard, bonusIterations);

    // Note: Bonus iterations are in order as listed here

    // Place Rooks (2 ct, place anywhere)
    PlaceRooks(whiteBoard, blackBoard, bonusIterations[0]);

    // Place Bishops (2ct: one on Dark Square, one on Light square)
    PlaceBishops(whiteBoard, blackBoard, bonusIterations[1]);

    // Place Knights (2 ct, place anywhere)
    PlaceKnight(whiteBoard, blackBoard, bonusIterations[2]);

    // Place Queens (1 ct, anywhere)
    PlaceQueens(whiteBoard, blackBoard, bonusIterations[3]);

    // Place Kings (1 ct, re-run if check)
    PlaceKing()

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
                printf("%c ", ToLowerCase(blackBoard[i][j]));
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
            if(whiteBoard[rng][i] != '.' && blackBoard[7-rng][7-i] != '.')
            {
                i--;

                //printf("Duplicate found at (%d, %d)!\n\n", rng, i);

                continue;
            }    
            
            whiteBoard[rng][i] = 'P';
            blackBoard[7 - rng][7 - i] = 'P';
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
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[7 - rng1][7 - rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'R';
            blackBoard[7 - rng1][7 - rng2] = 'R';
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
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[7 - rng1][7 - rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'B';
            blackBoard[7 - rng1][7 - rng2] = 'B';
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
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[7 - rng1][7 - rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'K';
            blackBoard[7 - rng1][7 - rng2] = 'K';
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
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[7 - rng1][7 - rng2] != '.')
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the queen there
        else
        {
            whiteBoard[rng1][rng2] = 'Q';
            blackBoard[7 - rng1][7 - rng2] = 'Q';
        }
    }
}

void PlaceKing(char whiteBoard[8][8], char blackBoard[8][8])
{
    int rng1 = rand() % 10;
    int rng2 = rand() % 10;

    for(int i = 0; i < 1; i++)
    {
        if(whiteBoard[rng1][rng2] != '.' || blackBoard[7 - rng1][7 - rng2] != '.' || Check(whiteBoard, blackBoard, rng1, rng2))
        {
            i--;
            continue;
        }
        else
        {
            whiteBoard[rng1][rng2] = 'K';
            blackBoard[7 - rng1][7 - rng2] = 'K';
            break;
        }

    }
}

int Check(char whiteBoard[8][8], char blackBoard[8][8], int posX, int posY)
{
    // return 0 = false
    // return 1 = true

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            
        }
    }
    
    return 0;
}
#pragma endregion