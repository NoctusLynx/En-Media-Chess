// References
#pragma region
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>
#include "ChessUtilities.h"

bool MainMenu(bool* debug);
void PrintGreeting(void);    
void GenerateBoard(bool debug);
void PrintBoard(char* board[8][8]);
void PrintLine(void);
void InitializeBoard(char* board[8][8]);

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
    scanf("%d", &input);
    switch(input)
    {
        // Generates the board
        case 1:
        GenerateBoard(*debug);
        
        // Exits the program via user input
        case 2:
        printf("Exiting...\n\n");
        return false;
        
        case 5969:
        if(*debug)
        {
            puts("\nDebug mode deactivated.\n\n");
            *debug = false;
        }
        else 
        {
            puts("\nDebug mode activated.\n\n");
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
    printf("Hello!\n\n");
    printf("Welcome to \"In Media Chess,\" a proceedurally random board generator for more interesting chess games!\n\n");
    printf("Please select one of the options below:\n");
    printf("1: Generate Board\n");
    printf("2: Exit Program");
    printf("\n\n");
}

void PrintLine(void)
{
    printf("  -------------------\n");
}

void GenerateBoard(bool debug)
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
    if(debug) puts("Adding pawns...");
    PlacePawns(board, bonusIterations, debug);
    if(debug) puts("Done.\n\n\n");
    if(debug) PrintBoard(board);
    
    // Note: Bonus iterations are in order as listed here

    // Place Rooks (2 ct, place anywhere)
    if(debug) puts("Adding rooks...");
    PlaceRooks(board, bonusIterations[0], debug);
    if(debug) puts("Done.\n\n\n");
    if(debug) PrintBoard(board);

    // Place Bishops (2ct: one on Dark Square, one on Light square)
    if(debug) puts("Adding bishops...");
    PlaceBishops(board, bonusIterations[1], debug);
    if(debug) puts("Done.\n\n\n");
    if(debug) PrintBoard(board);

    // Place Knights (2 ct, place anywhere)
    if(debug) puts("Adding knights...");
    PlaceKnights(board, bonusIterations[2], debug);
    if(debug) puts("Done.\n\n\n");
    if(debug) PrintBoard(board);

    // Place Queens (1 ct, anywhere)
    if(debug) puts("Adding queens...");
    PlaceQueens(board, bonusIterations[3], debug);
    if(debug) puts("Done.\n\n\n");
    if(debug) PrintBoard(board);

    // Place Kings (1 ct, re-run if check)
    if(debug) puts("Adding kings...");
    PlaceKing(board, debug);
    if(debug) puts("Board generation complete, printing board:\n\n\n");

    PrintBoard(board);
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

void PrintBoard(char* board[8][8])
{
    puts("    A B C D E F G H");
    
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

    printf("\n\n");
}

#pragma endregion