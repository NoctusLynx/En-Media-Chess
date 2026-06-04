// References
#pragma region
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "ChessUtilities.h"

// Compile and Execute:
// clear && gcc InMediaChess.c ChessUtilities.c -o InMediaChess.out && ./InMediaChess.out

bool MainMenu(bool* debug);
void PrintGreeting(void);    
void GenerateBoard(bool debug);
void PrintBoard(char* board[8][8]);
void PrintLine(bool orientation);
void InitializeBoard(char* board[8][8]);
void InputErrorMessage(void);

#pragma endregion

// Main and Ultilities
#pragma region
int main(void)
{
    bool debug = false;

    while(MainMenu(&debug))
    {

    }

    return 0;
}

bool MainMenu(bool* debug)
{
    setlocale(LC_ALL, "");

    PrintGreeting();

    srand(time(NULL));

    int input = -1;
    
    if(!scanf("%d", &input))
    {
        InputErrorMessage();
        return false;
    }
    
    switch(input)
    {
        // Generates the board
        case 1:
        GenerateBoard(*debug);
        
        // Exits the program via user input
        case 3:
        printf("Exiting...\n\n");
        return false;        

        case -1969667086:
        if(*debug)
        {
            puts("\n\tDEBUG MODE => OFF\n");
            *debug = false;
        }
        else 
        {
            puts("\nDEBUG MODE => ON\n");
            *debug = true;
        }  
        return true;

        // Exits the program via input error
        default:
        printf("ERROR: INPUT %d COULD NOT BE INTERPRETED, WILL EXIT PROGRAM NOW\n\n", input);
        return false;
    }
}

void PrintGreeting(void)
{
    puts("Hello!\n");
    puts("Welcome to \"In Media Chess,\" a proceedurally random board generator for more interesting chess games!");
    puts("Be sure to read the \"README.md\" file for information and rules!\n");
    puts("Please select one of the options below:");
    puts("1: Generate Board");
    puts("2: Exit Program");
    printf("\n");
}

void PrintLine(bool orientation)
{
    // orientation == true;     line opens down (top of board)
    // orientation == false;    line opens up (bottom of board)
    
    // Leading spaces
    printf("  ");
    
    // Prints the top-left or bottom-left corner
    orientation ? printf("\u250C") : printf("\u2514");
    
    // Horizontal line
    for(int i = 0; i < 17; i++) printf("\u2500");
    
    // Prints top-right or bottom-right corner
    orientation ? printf("\u2510") : printf("\u2518");
    
    // Newline
    printf("\n");
}

void GenerateBoard(bool debug)
{
    char* board[8][8];
    int bonusIterations[4] = {0, 0, 0, 0};
    char* captured[16] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};
    InitializeBoard(board);
    
    /*
    Generation notes:
    1. No more than 16 pieces for each player
    2. No more than 8 pawns
    3. Pawn has 20% chance, each, to not exist, 5% chance to be promoted to a different piece
    4. All other pieces (except King) have a 10% chance to not exist
    */
    
    // Place Pawns (8 ct, not on first or final row)
    debug ? puts("\nGenerating Pawns:") : printf("\nGenerating");
    PlacePawns(board, bonusIterations, captured, debug);
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board);
    }
    else
        printf(".");
    
    // Note: Bonus iterations are in order as listed here

    // Place Rooks (2 ct, place anywhere)
    debug ? puts("Generating Rooks:") : (void)0;
    PlaceRooks(board, bonusIterations[0], captured, debug);
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board);
    }
    else
        printf(".");

    // Place Bishops (2ct: one on Dark Square, one on Light square)
    debug ? puts("Generating Bishops:") : (void)0;
    PlaceBishops(board, bonusIterations[2], captured, debug);
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board);
    }
    else
        printf(".");

    // Place Knights (2 ct, place anywhere)
    debug ? puts("Generating Knights:") : (void)0;
    PlaceKnights(board, bonusIterations[1], captured, debug);
    if(debug)
    {
        puts("\tDone.\n");
        PrintBoard(board);
    }
    else
        printf(".");

    // Place Queens (1 ct, anywhere)
    debug ? puts("Generating Queens:") : (void)0;
    PlaceQueens(board, bonusIterations[3], captured, debug);
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board);
    }
    else
        printf(".");

    // Place Kings (1 ct, re-run if check)
    debug ? puts("Generating Kings:\n") : (void)0;
    PlaceKing(board, debug);
    debug ? puts("\nBoard generation complete, printing board:\n") : puts("\nDone.\n");

    PrintBoard(board);
}

void InitializeBoard(char* board[8][8])
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if((i + j) % 2 == 0)
            {
                board[i][j] = ChessPiece("WS");

            }
            else
            {
                board[i][j] = ChessPiece("BS");

            }
            
        }
    }
}

void PrintBoard(char* board[8][8])
{
    puts("    A B C D E F G H");
    
    PrintLine(true);

    for(int i = 0; i < 8; i++)
    {
        // Prints row header
        printf("%d \u2502 ", 8 - i);
        
        for(int j = 0; j < 8; j++)
        {
            printf("%s ", board[i][j]);
        }

        printf("\u2502\n");

    }

    PrintLine(false);

    printf("\n");
}

void InputErrorMessage(void)
{
    puts("ERROR: Unable to read user input!");
}

#pragma endregion