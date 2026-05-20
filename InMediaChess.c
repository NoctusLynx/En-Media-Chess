#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void PrintGreeting(void);    
void GenerateBoard(void);
void PrintBoard(char whiteBoard[8][8], char blackBoard[8][8]);
void PrintLine(void);
void InitializeBoards(char WhiteBoard[8][8], char BlackBoard[8][8]);
char ToLowerCase(char letter);
void PlacePawns(char whiteBoard[8][8], char blackBoard[8][8], int bonusIterations[4]);

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

void GenerateBoard(void)
{
    char whiteBoard[8][8];
    char blackBoard[8][8];
    int bonusIterations[4] = {0, 0, 0, 0};
    InitializeBoards(whiteBoard, blackBoard);

    /*
    Generation notes:
    1. No more than 16 pieces for each
    2. No more than 8 pawns
    3. Pawn has 20% chance, each, to not exist, 5% chance to be promoted to a different piece
    4. All other pieces (except King) have a 10% chance to not exist
    */
    
    // Place Pawns (8 ct, not on first or final row)
    PlacePawns(whiteBoard, blackBoard, bonusIterations);

    // Place Queens (1 ct, anywhere)

    // Place Bishops (2ct: one on Dark Square, one on Light square)

    // Place Rooks (2 ct, place anywhere)

    // Place Knights (2 ct, place anywhere)

    // Place Kings (1 ct, re-run if check)

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
                printf("X ", i, j);
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
        
        else if(rng < 2)
        {
            continue;
        }
        
        else
        {
            // Selects a spot on the column
            rng = rand() % 6 + 1;
            
            // Checks if that space is available
            if(whiteBoard[rng][i] != '.' && blackBoard != '.')
            {
                i--;

                printf("Duplicate found at (%d, %d)!\n\n", rng, i);

                continue;
            }    
            
            whiteBoard[rng][i] = 'P';
            blackBoard[7 - rng][7 - i] = 'P';
        }

    }
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
        
        case 'K':
        return 'k';

        case 'Q':
        return 'q';

        case 'B':
        return 'b';

        case 'N':
        return 'n';

        case 'R':
        return 'r';

        default:
        printf("ERROR USING \"ToLowerCase\" FUNCTION!");
        return '\0';
    }
}