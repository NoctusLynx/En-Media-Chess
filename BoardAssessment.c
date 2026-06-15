#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Utility Functions
#pragma region

// Takes a two-letter string, returns a UNICODE-8 chess piece
char* ChessPiece( char code[ 3 ] )
{
    // Parses the first letter of the string
    switch( code[ 0 ] )
    {
        // Black Pieces
        case 'B':
        {
            switch( code[ 1 ] )
            {
                // Black King
                case 'K':   
                {   return "\u265A";    }
                
                // Black Queen
                case 'Q':   
                {   return "\u265B";    }
    
                // Black Rook
                case 'R':   
                {   return "\u265C";    }
    
                // Black Bishop
                case 'B':   
                {   return "\u265D";    }
                
                // Black Knight
                case 'N':   
                {   return "\u265E";    }
    
                // Black Pawn
                case 'P':   
                {   return "\u265F";    }
    
                // Black Space
                case 'S':   
                {   return "\u25AA";    }
            }
            break;
        }

        // White Pieces
        case 'W':
        {
            switch( code[ 1 ] )
            {
                // White King
                case 'K':   
                {   return "\u2654";    }
        
                // White Queen
                case 'Q':   
                {   return "\u2655";    }
        
                // White Rook
                case 'R':   
                {   return "\u2656";    }
        
                // White Bishop
                case 'B':   
                {   return "\u2657";    }
                
                // White Knight
                case 'N':   
                {   return "\u2658";    }
                
                // White Pawn
                case 'P':   
                {   return "\u2659";    }
    
                // White Space
                case 'S':   
                {   return "\u25AB";    }
            }
            break;
        }
    }

    // If the string entered does not match any of the above valid inputs, returns 'X' as an error.
    return "X";
}

// Tests if a given board coordinate is within the bounds of the chess board
bool IsOnBoard( int input )
{
    // If the coordinate is on the board, return true;
    if( ( 0 <= input ) && ( input <= 7 ) )    
    {   return true;   }
    
    // Otherwise, return false
    else    
    {   return false;   }
}

// Checks if a given board space is empty or not
bool SpaceOccupied( char* boardSpace )
{
    // strcmp() returns 0 ( false ) when the two strings are the same

    // If the string at the board space matches any of these strings, return false
    if( !strcmp( boardSpace , ChessPiece( "BS" ) ) )
    {   return false;   }
    
    if( !strcmp( boardSpace , ChessPiece( "WS" ) ) )
    {   return false;   }
    
    if( !strcmp( boardSpace , "X" ) )
    {   return false;   }
    
    if( !strcmp( boardSpace , " " ) )
    {   return false;   }

    // Else, return true
    return true;
}

// Add captured pieces to a list
void AddToCaptured( char* chessPiece , char* captured[ 16 ] )
{
    // Scans the list of captured pieces
    for( int i = 0; i < 16; i++ )
    {
        // Stops at the first empty spot, and fills it with a captured  piece
        if( !strcmp( "" , captured[ i ] ) )
        {
            captured[ i ] = chessPiece;
            break;
        }
        
        // Otherwise, if the spot if full, skip to the next spot
        else
        {   continue;   }
    }
}

// Scans the pawnCodes[] array to find the frequency of a particular key
int ScanPawnCodes( int key , int pawnCodes[ 8 ] )
{
    int sum = 0;

    // Scans pawnCodes[] for the key value, and increments sum for every match it finds
    for( int i = 0; i < 8; i++ )
    {   sum += !( pawnCodes[ i ] - key ) ? 1 : 0;   }

    // Closes function and returns sum
    return sum;
}

#pragma endregion

// Printing function
#pragma region

// Prints a debug message to the console indicating which Black pieces at which location is checking the White King at its location
void CheckMessage( char* checkingPiece , int checkX , int checkY , int kingX , int kingY )
{
    printf( "\t%s at %d%c checks %s at %d%c\n" , checkingPiece , 7 - checkX + 1 , ( char )( checkY + 65 ) , ChessPiece( "WK" ) , 7 - kingX + 1 , ( char )( kingY + 65 ) );
}

// Takes a chess piece and swaps its team ( White -> Black; Black -> White )
char* SwapPiece( char* chessPiece )
{
    // Pawns
    if( true )
    {
        // White Pawn -> Black Pawn
        if( !strcmp( chessPiece , ChessPiece( "WP" ) ) )   
        {   return ChessPiece( "BP" );  }
    
        // Black Pawn-> White Pawn
        if( !strcmp( chessPiece , ChessPiece( "BP" ) ) )   
        {   return ChessPiece( "WP" );  }
    }
    
    // Rooks
    if( true )
    {
        // White Rook -> Black Rook
        if( !strcmp( chessPiece , ChessPiece( "WR" ) ) )   
        {   return ChessPiece( "BR" );  }
    
        // Black Rook -> White Rook
        if( !strcmp( chessPiece , ChessPiece( "BR" ) ) )   
        {   return ChessPiece( "WR" );  }
    }
    
    // Knights
    if( true )
    {
        // White Knight -> Black Knight
        if( !strcmp( chessPiece , ChessPiece( "WN" ) ) )   
        {   return ChessPiece( "BN" );  }
    
        // Black Knight -> White Knight
        if( !strcmp( chessPiece , ChessPiece( "BN" ) ) )   
        {   return ChessPiece( "WN" );  }
    }
    
    // Bishops
    if( true )
    {
        // White Bishop -> Black Bishop
        if( !strcmp( chessPiece , ChessPiece( "WB" ) ) )   
        {   return ChessPiece( "BB" );  }
    
        // Black Bishop -> White Bishop
        if( !strcmp( chessPiece , ChessPiece( "BB" ) ) )   
        {   return ChessPiece( "WB" );  }
    }

    // Queens
    if( true )
    {
        // White Queen -> Black Queen
        if( !strcmp( chessPiece , ChessPiece( "WQ" ) ) )   
        {   return ChessPiece( "BQ" );  }
    
        // Black Queen -> White Queen
        if( !strcmp( chessPiece , ChessPiece( "BQ" ) ) )   
        {   return ChessPiece( "WQ" );  }
    }

    // Kings
    if( true )
    {
        // White King -> Black King
        if( !strcmp( chessPiece , ChessPiece( "WK" ) ) )   
        {   return ChessPiece( "BK" );  }
        
        // Black King -> White King
        if( !strcmp( chessPiece , ChessPiece( "BK" ) ) )   
        {   return ChessPiece( "WK" );  }
    }
}

// Prints a debug message to the console indicating which piece has been placed and at what position
void PlacementMessage( char* placedPiece , int rank , int file )
{
    printf( "\t( %s , %s ) => ( %d%c , %d%c )\n" , placedPiece , SwapPiece( placedPiece ) , 7 - rank + 1 , ( char )( file + 65 ) , 7 - ( 7 - rank ) + 1 , ( char )( 7 - file + 65 ) );
}

// Converts a UNICODE-8 chess piece to FEN chess piece characters
char InvChessPiece( char* chessPiece )
{
    // White Pawn   -> Uppercase P
    if( !strcmp( chessPiece , ChessPiece( "WP" ) ) )   
    {   return 'P'; }
    
    // Black Pawn   -> Lowercase P
    if( !strcmp( chessPiece , ChessPiece( "BP" ) ) )   
    {   return 'p'; }

    // White Rook   -> Uppercase R
    if( !strcmp( chessPiece , ChessPiece( "WR" ) ) )   
    {   return 'R'; }
    
    // Black Rook   -> Lowercase R
    if( !strcmp( chessPiece , ChessPiece( "BR" ) ) )   
    {   return 'r'; }

    // White Knight -> Uppercase N
    if( !strcmp( chessPiece , ChessPiece( "WN" ) ) )   
    {   return 'N'; }
    
    // Black Knight -> Lowercase N
    if( !strcmp( chessPiece , ChessPiece( "BN" ) ) )   
    {   return 'n'; }

    // White Bishop -> Uppercase B
    if( !strcmp( chessPiece , ChessPiece( "WB" ) ) )   
    {   return 'B'; }
    
    // Black Bishop -> Lowercase B
    if( !strcmp( chessPiece , ChessPiece( "BB" ) ) )   
    {   return 'b'; }
    
    // White Queen  -> Uppercase Q
    if( !strcmp( chessPiece , ChessPiece( "WQ" ) ) )   
    {   return 'Q'; }
    
    // Black Queen  -> Lowercase Q
    if( !strcmp( chessPiece , ChessPiece( "BQ" ) ) )   
    {   return 'q'; }

    // White King   -> Uppercase K
    if( !strcmp( chessPiece , ChessPiece( "WK" ) ) )   
    {   return 'K'; }
    
    // Black King   -> Lowercase K
    if( !strcmp( chessPiece , ChessPiece( "BK" ) ) )   
    {   return 'k'; }

    // Else, returns the Null Char as an error message
    return '\0';
}

// Prints the board state a FEN string
void OutputFEN( char* board[ 8 ][ 8 ] )
{
    // More info: https://en.wikipedia.org/wiki/Forsyth%E2%80%93Edwards_Notation
    
    // Prints FEN code header
    printf( "FEN: " );

    // A counter for consecutive empty spaces
    int emptySpace = 0;

    // Print characters based on pieces and their positions
    for( int i = 0; i < 8; i++ )
    {
        for( int j = 0; j < 8; j++ )
        {
            // If there is a chess piece here, print it
            if( InvChessPiece( board[ i ][ j ] ) )
            {
                // But first, print then wipe the number of empty spaces before finding this piece
                if( emptySpace )
                {
                    printf( "%d" , emptySpace );
                    emptySpace = 0;
                }
                
                // Then print the piece
                printf( "%c" , InvChessPiece( board[ i ][ j ] ) ); 
            }
            // If there is not a chess piece here, increment a number instead; print that number on next chess piece, or on end of row
            else
            {   emptySpace++;   }

        }
        
        // On end of row, print and then reset the emptySpace counter
        if( emptySpace )
        {
            printf( "%d" , emptySpace );
            emptySpace = 0;
        }
        
        // On all but final row
        if( i < 7 )
        {   printf( "/" );  }
    }

    // Whose turn is it ( will always be White )
    printf( " w " );

    // Determine castling rights
    if( true )
    {
        // Catling rights booleans
        bool K = false , Q = false , k = false , q = false;
    
        // Check if black king is where it's supposed to be for castling rights
        if( !strcmp( board[ 0 ][ 4 ] , ChessPiece( "BK" ) ) )
        {
            if( !strcmp( board[ 0 ][ 0 ] , ChessPiece( "BR" ) ) )
            {   q = true;   }

            if( !strcmp( board[ 0 ][ 7 ] , ChessPiece( "BR" ) ) )
            {   k = true;   }
        }   
        
        // Check if white king is where it's supposed to be for castling rights
        if( !strcmp( board[ 7 ][ 4 ] , ChessPiece( "WK" ) ) )
        {
            if( !strcmp( board[ 7 ][ 0 ] , ChessPiece( "WR" ) ) )
            {   Q = true;   }

            if( !strcmp( board[ 7 ][ 7 ] , ChessPiece( "WR" ) ) )
            {   K = true;   }
        }
        
        // Prints relevant castling rights
        K ? printf( "K" ) : ( void )0;
        Q ? printf( "Q" ) : ( void )0;
        k ? printf( "k" ) : ( void )0;
        q ? printf( "q" ) : ( void )0;
        
        // If any of the kings can catle in either direction, print a spacer
        if( K || Q || k || q )
        {   printf( " " );  }
    }

    // Determine En Passant rights ( is disabled in this version )
    printf( "- ");

    // Turn clocks ( As this is in the middle of a game, these will be randomized within a range)
    printf( "%d " , rand() % 40 + 1 );
    printf( "%d" , rand() % 100 + 21 );

    // Prints a spacer
    printf( "\n\n" );

}

#pragma endregion