// References
#pragma region

#include <stdio.h>              // Used for input and output functions
#include <stdlib.h>             // Used for random number generation
#include <time.h>               // Used to save the number of seconds since the Unix epoch as the seed for random number generation
#include <stdbool.h>            // Used to implement boolean values for readability
#include <string.h>             // Used to implement string comparisons
#include <locale.h>             // Used to implement UNICODE-8 support
#include "PlacementLogic.h"     // Used to implement functions for the placement of chess pieces on the board
#include "BoardAssessment.h"    // Used to implement functions for calculations and print methods related to board generation

// Compile and Execute:
// clear && gcc InMediaChess.c ChessUtilities.c -o InMediaChess.out && ./InMediaChess.out

bool MainMenu(bool* debug); 
void PrintGreeting(void);    
void GenerateBoard(bool debug);
void PrintBoard(char* board[8][8], char* captured[16]);
void PrintLine(bool orientation);
void InitializeBoard(char* board[8][8]);
void InputErrorMessage(void);

#pragma endregion

// Main and Ultilities
#pragma region

// Decides when to close the program
int main(void)
{
    // A flag for debug mode
    bool debug = false;

    // Will continue to loop so long as MainMenu() != 0, and MainMenu() will continue to fire until then
    while(MainMenu(&debug)) (void)0;

    // Program closes when MainMenu() = 0
    return 0;
}

// Takes and interprets user input
bool MainMenu(bool* debug)
{
    // Lets the code interpret UNICODE-8 characters, used in visualizing the generated board
    setlocale(LC_ALL, "");
    
    // Sets the seed to the number of seconds since 00:00:00 (UTC), Jan 1, 1970.
    srand(time(NULL));

    // Prints the greeting and prompt
    PrintGreeting();

    // Input variable
    int input = -1;
    
    // Takes input from user
    if(!scanf("%d", &input))
    {
        // Closes the program with an error message if the input is invalid
        InputErrorMessage();
        return false;
    }

    // Parses the input, and performs actions based on the input
    switch(input)
    {
        // Generates the board
        case 1:
        GenerateBoard(*debug);
        
        // Exits the program via user input
        case 2:
        printf("Exiting...\n\n");
        return false;        

        // Activates Debug Mode; value is equivalent to the overflowed value of 88224646130
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

// Prints prompt for user
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

// Prints lines during board printing
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

// Generates the Chess Board
void GenerateBoard(bool debug)
{
    // The board
    char* board[8][8];
    
    // List of captured pieces
    char* captured[16] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "", ""};

    // Bishop codes: -1 = none; 0 = light; 1 = dark
    int bishopCodes[] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

    // Pawn codes: 0 = pawn captured/promoted; 1 = pawn exists
    int pawnCodes[] = {1, 1, 1, 1, 1, 1, 1, 1};

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
    
    PlacePawns(board, captured, pawnCodes, debug);
    
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board, captured);
    }
    else printf(".");    
    
    // Note: Bonus iterations are in order as listed here

    // Place Rooks (2 ct, place anywhere)
    debug ? puts("Generating Rooks:") : (void)0;
    
    PlaceRooks(board, ScanPawnCodes(-1, pawnCodes), captured, debug);
    
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board, captured);
    }
    else printf(".");
    
    // Place Knights (2 ct, place anywhere)
    debug ? puts("Generating Knights:") : (void)0;
    
    PlaceKnights(board, ScanPawnCodes(-2, pawnCodes), captured, debug);
    
    if(debug)
    {
        puts("\tDone.\n");
        PrintBoard(board, captured);
    }
    else printf(".");
    
    // Place Bishops (2ct: one on Dark Square, one on Light square)
    debug ? puts("Generating Bishops:") : (void)0;
    
    PlaceBishops(board, ScanPawnCodes(-3, pawnCodes), captured, pawnCodes, bishopCodes, debug);
    
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board, captured);
    }
    else printf(".");


    // Place Queens (1 ct, anywhere)
    debug ? puts("Generating Queens:") : (void)0;
    
    PlaceQueens(board, ScanPawnCodes(-4, pawnCodes), captured, debug);
    
    if(debug) 
    {
        puts("\tDone.\n");
        PrintBoard(board, captured);
    }
    else printf(".");

    // Shifts pawns to simulate pawn captures
    debug ? puts("Shifting Pawns...") : (void)0;
    
    ShiftPawns(board, captured, pawnCodes, bishopCodes, debug);
    
    if(debug)
    {
        puts("\tDone.\n");
        PrintBoard(board, captured);
    }
    else printf(".");
    
    // Place Kings (1 ct, re-run if check)
    debug ? puts("Generating Kings:\n") : (void)0;
    
    PlaceKing(board, debug);
    
    debug ? puts("\tDone.\n") : (void)0;

    // Prints a message to indicate that board generation is complete
    debug ? puts("Board generation complete, printing board:\n") : puts("\nDone.\n");

    // Prints the board
    PrintBoard(board, captured);

    // Encodes the board into an FEN string and prints that string
    OutputFEN(board);
}

// Populates the empty board with light and dark squares
void InitializeBoard(char* board[8][8])
{
    // Scans the board
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            // Place a light-square if the sum of coordinates of this space are even
            if((i + j) % 2 == 0)    board[i][j] = ChessPiece("WS");
            
            // Place a dark-square if the sum of coordinates of this space are odd
            else                    board[i][j] = ChessPiece("BS");
            
        }
    }
}

// Prints the current chess board
void PrintBoard(char* board[8][8], char* captured[16])
{
    // Board File headers
    puts("    A B C D E F G H");
    
    // Prints the top board border
    PrintLine(true);

    // For each row of the board
    for(int i = 0; i < 8; i++)
    {
        // Prints Rank header and left-most board border
        printf("%d \u2502 ", 8 - i);
        
        // Prints each piece or empty space in this row
        for(int j = 0; j < 8; j++)      printf("%s ", board[i][j]);

        // Prints right-most board border
        printf("\u2502\n");
    }

    // Prints board bottom border
    PrintLine(false);

    // Prints a list of piece pre-captured by White
    printf("\nWhite Captured: ");
    for(int i = 0; i < 16; i++)
    {
        // Stops reading if it finds an empty spot
        if(!strcmp("", captured[i]))    break; 

        // Else, keeps reading and printing captured pieces
        printf("%s ", SwapPiece(captured[i]));
    }

    // Prints a list of pieces pre-captured by Black
    printf("\nBlack Captured: ");
    for(int i = 0; i < 16; i++)
    {
        // Stops reading if it finds an empty spot in the captured array
        if(!strcmp("", captured[i]))    break;
        
        // Else, keeps reading and printing captured pieces
        printf("%s ", captured[i]);
    }
    
    // Spacer
    printf("\n\n");
}

// Error message for when user does not enter a valid input
void InputErrorMessage(void)
{
    puts("ERROR: Unable to read user input!");
}

#pragma endregion