// Refences
#pragma region

#include "PlacementLogic.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BoardAssessment.h"

#pragma endregion

#pragma region

// Executes Piece Placement
void PlacePiece( char* board[ 8 ][ 8 ] , char* chessPiece , int rank , int file , bool debug )
{
    debug ? PlacementMessage( chessPiece , rank , file ) : ( void )0;

    // Place Black Pawn
    board[ rank ][ file ] = chessPiece;

    // Place White Pawn
    board[ 7 - rank ][ 7 - file ] = SwapPiece( chessPiece );
}

// Decide where to place Pawns
void PlacePawns( char* board[ 8 ][ 8 ] , char* captured[ 16 ] , int pawnCodes[ 8 ] , bool debug )
{
    // Iterates 8 times, one for each possible pawn
    for( int i = 0; i < 8; i++ )
    {
        // Randomize values
        int rng = rand() % 10;

        // 10% chance to be promoted to different piece
        if( rng < 1 )
        {
            debug ? printf( "\t(  %s , %s ) => " , ChessPiece( "BP" ) , ChessPiece( "WP" ) ) : ( void )0;
            
            // Rolls a new value and parses it
            rng = rand() % 4;
            switch( rng )
            {
                // Promote to Rook
                case 0:
                {
                    debug ? printf( "( %s  , %s  )\n" , ChessPiece( "BR" ) , ChessPiece( "WR" ) ) : ( void )0;
                    
                    // Encodes which the Pawn became a Rook
                    pawnCodes[ i ] = -1;
                
                    break;
                }

                // Promote to Knight
                case 1:
                {
                    debug ? printf( "( %s  , %s  )\n" , ChessPiece( "BN" ) , ChessPiece( "WN" ) ) : ( void )0;
                    
                    // Encodes which Pawn became a Knight
                    pawnCodes[ i ] = -2;

                    break;
                }

                // Promote to Bishop
                case 2:
                {
                    debug ? printf( "( %s  , %s  )\n" , ChessPiece( "BB" ) , ChessPiece( "WB" ) ) : ( void )0;
                    
                    // Encodes which Pawn became a Bishop
                    pawnCodes[ i ] = -3;

                    break;
                }

                // Promote to Queen
                case 3:
                {
                    debug ? printf( "( %s  , %s  )\n" , ChessPiece( "BQ" ) , ChessPiece( "WQ" ) ) : ( void )0;
                    
                    // Encodes which Pawn became a Queen
                    pawnCodes[ i ] = -4;
                    
                    break;
                }
            }
        }
        
        // 20% chance to be pre-captured
        else if( rng < 3 )
        {
            debug ? printf( "\t( %s , %s ) => ( X  , X  )\n" , ChessPiece( "BP" ) , ChessPiece( "WP" ) )  : ( void )0;
            
            // Sets this Pawn's code to 0 ( pre-captured )
            pawnCodes[ i ] = 0;

            // Add this pre-captured piece to captured[]
            AddToCaptured( ChessPiece( "WP" ) , captured );
            
            continue;
        }
        
        // Otherwise, spawn a White and Black pawn
        else
        {
            // Selects a spot on the column
            rng = rand() % 3 + 1;
            
            // Re-rolls the position if it's occupied
            if( SpaceOccupied( board[ rng ][ i ] ) || SpaceOccupied( board[ 7 - rng ][ 7 - i ] ) )
            {
                i--;

                continue;
            }    
            
            // If the space is not occupied, then place the Pawn there
            PlacePiece( board , ChessPiece( "BP" ) , rng , i , debug );
        }

    }
}

// Decide where to place Rooks
void PlaceRooks( char* board[ 8 ][ 8 ] , int extraRooks , char* captured[ 16 ] , bool debug )
{
    debug ? printf( "\tTotal %s : 2 + %d = %d\n" , ChessPiece( "WR" ) , extraRooks , 2 + extraRooks ) : ( void )0;
    
    // Iterates twice for the two starting rooks, then more times based on pawns promoted to rooks
    for( int i = 0; i < 2 + extraRooks; i ++ )
    {
        int coin = rand() % 10;

        // 10% chance to be pre-captured
        if( coin < 1 )
        {
            debug ? printf( "\t( %s , %s ) => ( X  , X  )\n" , ChessPiece( "BR" ) , ChessPiece( "WR" ) ) : ( void )0;
            
            // Add this pre-captured piece to captured[]
            AddToCaptured( ChessPiece( "WR" ) , captured );
            
            continue;
        }
            
        // Roll the coordinates of this Rook
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if( SpaceOccupied( board[ rng1 ][ rng2 ] ) || SpaceOccupied( board[ 7 - rng1 ][ 7 - rng2 ] ) )
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the Rook there
        PlacePiece( board , ChessPiece( "BR" ) , rng1 , rng2 , debug );
    }
}

// Decide where to place Bishops
void PlaceBishops( char* board[ 8 ][ 8 ] , int extraBishops , char* captured[ 16 ] , int pawnCodes[ 8 ] , int bishopCodes[ 10 ] , bool debug )
{
    debug ? printf( "\tTotal %s : 2 + %d = %d\n" , ChessPiece( "WB" ) , extraBishops , 2 + extraBishops ) : ( void )0;
    
    // Iterates twice for the two starting Bishops, then more times based on Pawns promoted to Bishops
    for( int i = 0; i < 2 + extraBishops; i ++ )
    {
        int coin = rand() % 10;

        // 10% chance to not exist
        if( coin < 1 )
        {
            debug ? printf( "\t( %s , %s ) => ( X  , X  )\n" , ChessPiece( "BB" ) , ChessPiece( "WB" ) ) : ( void )0;
            
            // Adds this pre-captured piece to captured[]
            AddToCaptured( ChessPiece( "WB" ) , captured );
            
            // Wipes the color code from Bishop Codes
            bishopCodes[ i ] = -1;
            
            continue;
        }
            
        // 50% chance to be a light or dark square bishop
        coin = rand() % 2;

        // Guarantees that the first two bishops are on opposite colored squares for fairness
        if( i == 0 )          
        {   coin = 0;   }

        else if( i == 1 )     
        {   coin = 1;   }

        // Check for the color of promoted pawns
        else if( i > 1 )
        {
            // Scans the pawn codes array
            for( int i = 0; i < 8; i++ )
            {
                // If it finds a promoted bishop
                if( pawnCodes[ i ] == -3 )
                {
                    // Set coin to match the position of that pawn in pawnCodes[]
                    coin = ( i % 2 == 0 ) ? 0 : 1;

                    if( debug )
                    {
                        printf( "\tpawnCodes at i = %d results in " , i );
    
                        printf( coin ? "dark-square bishop\n" : "light-square bishop\n" );
                    }

                    // Wipe that entry from pawnCodes[]
                    pawnCodes[ i ] = 0;
                    break;
                }

            }
        }

        // Select location to spawn the bishop
        int rng1 = 2 * ( rand() % 4 );
        int rng2 = 2 * ( rand() % 4 );

        // If coin is even, then both rng values are even; if coid is odd, only one of the rng values are odd
        // Recall: coin = 0 => Light-Square Bishop; coin = 1 => Dark-Square Bishop
        if( coin == 1 )
        {
            bishopCodes[ i ] = 1;
            rng1++;
            if( rng1 >= 8 )
                rng1 = 0;
        }
        else
        {   bishopCodes[ i ] = 0; }

        // Another 50/50 chance to fire
        if( rand() % 2 )
        {
            // Increment both rng1 and rng2
            ++rng1;
            ++rng2;

            // If either is off the board, wrap them back to 0. 
            rng1 = ( rng1 > 7 ) ? 0 : rng1;
            rng2 = ( rng2 > 7 ) ? 0 : rng2;
        }

        // if the space is not within the bounds of the board, re-roll position
        if( !IsOnBoard( rng1 ) || ! IsOnBoard( rng2 ) )
        {
            i--;
            continue;
        }

        // If the space is occupied, re-roll position
        if( SpaceOccupied( board[ rng1 ][ rng2 ] ) || SpaceOccupied( board[ 7 - rng1 ][ 7 - rng2 ] ) )
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the Bishop there
        PlacePiece( board , ChessPiece( "BB" ) , rng1 , rng2 , debug );
    }
}

// Decide where to place Knights
void PlaceKnights( char* board[ 8 ][ 8 ] , int extraKnights , char* captured[ 16 ] , bool debug )
{
    debug ? printf( "\tTotal %s: 2 + %d = %d\n" , ChessPiece( "WN" ) , extraKnights , 2 + extraKnights ) : ( void )0;
    
    // Iterates twice, once for each starting Knight, then more based on pawns that promoted to Knights
    for( int i = 0; i < 2 + extraKnights; i ++ )
    {
        // 10% chance to pre-capture this Knight
        if( rand() % 10 )
        {
            debug ? printf( "\t( %s , %s ) => ( X  , X  )\n" , ChessPiece( "BN" ) , ChessPiece( "WN" ) ) : ( void )0;
            AddToCaptured( ChessPiece( "WN" ) , captured );
            continue;
        }

        // Otherwise, roll the Knight's position
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if( SpaceOccupied( board[ rng1 ][ rng2 ] ) || SpaceOccupied( board[ 7 - rng1 ][  7- rng2 ] ) )
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the Knight there
        PlacePiece( board , ChessPiece( "BN" ) , rng1 , rng2 , debug );
    }
}

// Decide where to place Queens
void PlaceQueens( char* board[ 8 ][ 8 ] , int extraQueens , char* captured[ 16 ] , bool debug )
{
    debug ? printf( "\tTotal %s: 2 + %d = %d\n" , ChessPiece( "WQ" ) , extraQueens , 2 + extraQueens ) : ( void )0;

    for( int i = 0; i < 1 + extraQueens; i ++ )
    {
        // 10% chance to be pre-captured
        if( ( rand() % 10 ) < 1 )
        {
            debug ? printf( "\t( %s ,  %s ) => ( X  , X  )\n" , ChessPiece( "BQ" ) , ChessPiece( "WQ" ) ) : ( void )0;
            AddToCaptured( ChessPiece( "WQ" ) , captured );
            continue;
        }

        // Otherwise, rolls the Queen's position
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        // If the space is occupied, re-roll position
        if( SpaceOccupied( board[ rng1 ][ rng2 ] ) || SpaceOccupied( board[ 7 - rng1 ][ 7 - rng2 ] ) )
        {
            i--;
            continue;
        }

        // If space is not occupied, then place the Queen there
        PlacePiece( board , ChessPiece( "BQ" ) , rng1 , rng2 , debug );
    }
}

// Decide where to place Kings
void PlaceKing( char* board[ 8 ][ 8 ] , bool debug )
{
    // Continues to iterate until the King is placed
    while( true )
    {
        // Rolls the King's position
        int rng1 = rand() % 8;
        int rng2 = rand() % 8;

        if( debug ) 
        {   
            printf( 
                "( %s , %s ) <=> ( %d%c , %d%c )\n" , 
                board[ rng1 ][ rng2 ] , board[ 7 - rng1 ][ 7 - rng2 ] , 7 - rng1 + 1 , 
                ( char )( rng2 + 65 ) , rng1 + 1 , ( char )( 7 - rng2 + 65 ) 
            ); 
        }
        
        // If thespace is occupied, re-roll the King's position
        if( SpaceOccupied( board[ rng1 ][ rng2 ] ) || SpaceOccupied( board[ 7 - rng1 ][ 7 - rng2 ] ) || Check( board , 7 - rng1 , 7 - rng2 , debug ) )
        {
            debug ? puts( "\tInvalid location, re-rolling king placement.\n" ) : ( void )0;
            continue;
        }
        
        // If space is not occupied, then place the King here, and exit the loop
        PlacePiece( board , ChessPiece( "BK" ) , rng1 , rng2 , debug );
        break;

    }
}

// Scans the board for check
bool Check( char* board[ 8 ][ 8 ] , int kingRank , int kingFile , bool debug )
{
    // return false =>  king is not in check
    // return true  =>  king is in check

    // Buffer variables for kingRank and kingFile
    int checkRank , checkFile;

    debug ? printf( "\tSpace available!\n\tScanning for check if %s  => %d%c...\n\n" , ChessPiece( "WK" ) , 7 - kingRank + 1 , ( char )( kingFile + 65 ) ) : ( void )0;
    
    // Check if attacked by a Rook or Queen
    if( true )
    {
        debug ?  puts( "Scanning for check by Rooks or Queens..." ) : ( void )0;
        
        // Resets n and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;
    
        // Scans southbound from the White King's would-be position until the board's edge
        while( IsOnBoard( ++checkRank ) && IsOnBoard( checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) ) 
            {   continue;   }
    
            // Returns true if it finds a Black Rook
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BR" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BR" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Returns true if it finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
                
                return true;
            }    

            // Exits loop if it finds anything else
            else    
            {   break;  }
        }
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;

        // Scans northbound from the White King's would-be position until the board's edge
        while( IsOnBoard( --checkRank ) && IsOnBoard( checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) ) 
            {   continue;   }
    
            // Returns true if it finds a Black Rook
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BR" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BR" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }  
            
            // Returns true if it find a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
    
            // Exits loop if it finds anything else
            else    
            {   break;  }
        }
    
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;

        // Scans eastbound from the White King's would-be position until the board's edge
        while( IsOnBoard( checkRank ) && IsOnBoard( ++checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) )     
            {   continue;   }
    
            // Returns true if it finds a Black Rook
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BR" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BR" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
                
                return true;
            }
    
            // Returns true if is finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
    
            // Exits the loop if it finds anything else
            else    
            {   break;  }
        }
    
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;

        // Scans westbound from the White King's would-be position until the board's edge
        while( IsOnBoard( checkRank ) && IsOnBoard( --checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) )     
            {   continue;   }
    
            // Returns true if it finds a Black Rook
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BR" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BR" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
                
                return true;
            }
            
            // Returns true if it finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
    
            // Exits the loop if it finds anything else
            else    
            {   break;  }
        }
        
        debug ? puts( "\tDone.\n" ) : ( void )0;
    }
    
    // Check if attacked by a Bishop or Queen
    if( true )
    {
        debug ? puts( "Scanning for checks by Bishops or Queens..." )  : ( void )0;
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;
    
        // Scans southeastbound from the White King's would-be position until the board's edge
        while( IsOnBoard( ++checkRank ) && IsOnBoard( ++checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) )     
            {   continue;   }
            
            // Returns true if it finds a Black Bishop
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BB" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BB" ) , checkRank , checkFile , kingRank , kingFile )  : ( void )0;
    
                return true;
            }
    
            // Returns true if it finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Exits the loop if it finds anything else
            else    
            {   break;  }
    
        }
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;
        
        // Scans northeastbound from the White King's would-be position until the board's edge
        while( IsOnBoard( --checkRank ) && IsOnBoard( ++checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) )     
            {   continue;   }
    
            // Returns true if it finds a Black Bishop
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BB" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BB" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Returns true if it finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Exits the loop if it finds anything else
            else    
            {   break;  }
        }
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;

        // Scans southwestbound from the White King's would-be position until the board's edge
        while( IsOnBoard( ++checkRank ) && IsOnBoard( --checkFile ) )
        {
            // Ignores empty spaces
            if( !SpaceOccupied( board[ checkRank ][ checkFile ] ) )     
            {   continue;   }
            
            // Returns true if it finds a Black Bishop
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BB" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BB" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
    
            // Returns true if it finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Exits the loop if it finds anything else
            else    
            {   break;  }
        }
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;

        // Scans northwestbound from the White King's would-be position until the board's edge
        while( IsOnBoard( --checkRank ) && IsOnBoard( --checkFile ) )
        {
            // Ignores empty spaces
            if( SpaceOccupied( board[ checkRank ][ checkFile ] ) )  
            {   continue;   }
            
            // Returns true if it finds a Black Bishop
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BB" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BB" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Returns true if it finds a Black Queen
            else if( !strcmp( board[ checkRank ][ checkFile ] , ChessPiece( "BQ" ) ) )
            {
                debug ? CheckMessage( ChessPiece( "BQ" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                return true;
            }
            
            // Exits the loop if it finds anything else
            else    
            {   break;  }
        }
        
        debug ? puts( "\tDone.\n" ) : ( void )0;   
    }
    
    // Check if attacked by a Knight
    if( true )
    {
        debug ? puts( "Scanning for checks by Knights..." ) : ( void )0;
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;
        
        // Down 2
        if( IsOnBoard( checkRank + 2 ) )
        {
            // Right 1
            if( IsOnBoard( checkFile + 1 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank + 2 ][ checkFile + 1 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank + 2 , checkFile + 1 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
            
            // Left 1
            if( IsOnBoard( checkFile - 1 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank + 2 ][ checkFile - 1 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank + 2 , checkFile - 1 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
            
        }
    
        // Up 2
        if( IsOnBoard( checkRank - 2 ) )
        {
            // Right 1
            if( IsOnBoard( checkFile + 1 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank - 2 ][ checkFile + 1 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank - 2 , checkFile + 1 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
            
            // Left 1
            if( IsOnBoard( checkFile - 1 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank - 2 ][ checkFile - 1 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank - 2  , checkFile - 1 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
        }
        
        // Down 1
        if( IsOnBoard( checkRank + 1 ) )
        {
            // Right 2
            if( IsOnBoard( checkFile + 2 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank + 1 ][ checkFile + 2 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank + 1 , checkFile + 2 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
    
            // Left 2
            if( IsOnBoard( checkFile - 2 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank + 1 ][ checkFile - 2 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank + 1 , checkFile - 2 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
        }
    
        // Up 1
        if( IsOnBoard( checkRank - 1 ) )
        {
            // Right 2
            if( IsOnBoard( checkFile + 2 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank - 1 ][ checkFile + 2 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BN" ) , checkRank - 1 , checkFile + 2 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
            
            // Left 2
            if( IsOnBoard( checkFile - 2 ) )
            {
                // Returns true if it finds a Black Knight
                if( !strcmp( board[ checkRank - 1 ][ checkFile - 2 ] , ChessPiece( "BN" ) ) )
                {
                    debug ? CheckMessage(  ChessPiece( "BN" )  , checkRank - 1 , checkFile - 2 , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
        }
        
        debug ? puts( "\tDone.\n" ) : ( void )0;
    }

    // Check if attacked by a Pawn or King
    if( true )
    {
        debug ? puts( "Scanning for checks by Pawns or Kings..." ) : ( void )0;
        
        // Resets checkRank and checkFile to the White King's would-be coordinates
        checkRank = kingRank , checkFile = kingFile;
        
        // Scans all spaces around the White King
        for( int a = -1; a <= 1; a++ )
        {
            for( int b = -1; b <= 1; b++ )
            {
                // Ignore the space containing the White King
                if( a == 0 && b == 0 )
                {   continue;   }
                
                // Skip spaces are outside the bounds of the board
                if( !IsOnBoard( checkRank + a ) || !IsOnBoard( checkFile + b ) )
                {   continue;   }
                
                // Checks for spaces that could hold an attacking pawn
                if( a == -1 || b != 0 )
                {
                    // Returns true if it finds a Black Pawn
                    if( !strcmp( board[ checkRank + a ][ checkFile + b ] , ChessPiece( "BP" ) ) )
                    {
                        debug ? CheckMessage( ChessPiece( "BP" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                        return true;
                    }
                }
                
                // Checks if an adjacent space contains a Black King
                if( !strcmp( board[ checkRank + a ][ checkFile + b ] , ChessPiece( "BK" ) ) )
                {
                    debug ? CheckMessage( ChessPiece( "BK" ) , checkRank , checkFile , kingRank , kingFile ) : ( void )0;
    
                    return true;
                }
            }
        }
        
        debug ? puts( "\tDone.\n" ) : ( void )0;
    }

    debug ? puts( "No checks found!" ) : ( void )0;
    
    // If all checks fail, return false
    return false;
}

// Decide how pawns should move during pre-captures
void ShiftPawns( char* board[ 8 ][ 8 ] , char* captured[ 16 ] , int pawnCodes[ 8 ] , int bishopCodes[ 10 ] , bool debug )
{
    // Count the number of captured pieces
    int numCaptured = 0;
    int captureCodes[ 5 ] = {0 , 0 , 0};
    
    // Checks if any Pawns have been placed on the board, aborts ShiftPawns() if none where found
    for( int i = 0; i < 8; i++ )
    {
        if( pawnCodes[ i ] == 1 )
        {
            debug ? puts( "\tPawns found, continuing with function." ) : ( void )0;
            break;
        }
        else if( i == 7 )
        {
            debug ? puts( "\tNo pawns found, aborting PawnShift()..." ) : ( void )0;
            return;
        }    
    }

    // Iterates across the length of captured[]
    for( int i = 0; i < 16; i++ )
    {
        // If it finds an empty spot, stop iterating
        if( !strcmp( captured[ i ] , "" ) )
        {   break;  }

        // If something is in this spot
        else
        {
            // Increment the first position in captureCodes[] for Pawn Captures
            if( !strcmp( captured[ i ] , ChessPiece( "WP" ) ) )         captureCodes[ 0 ]++;

            // Increment the second position in captureCodes[] for Bishop Captures
            else if( !strcmp( captured[ i ] , ChessPiece( "WB" ) ) )    captureCodes[ 1 ]++;

            // Incremenets the third position in captureCodes[] for general captures
            else    captureCodes[ 2 ]++;

            // Increments a total capture counter
            numCaptured++;
        }    
    }

    // If no pieces were captured, force quit the function
    if( numCaptured <= 0 )
    {   return; }

    debug ? printf( "\tNumber of captured pieces: %d\n" , numCaptured ) : ( void )0;

    int threshold = 5;

    // Parse the board for pawns
    for( int i = 0; i < 8; i++ )
    {
        for( int j = 0; j < 8; j++ )
        {
            // Fires if a pawn is found
            if( !strcmp( board[ i ][ j ] , ChessPiece( "WP" ) ) || !strcmp( board[ i ][ j ] , ChessPiece( "BP" ) ) )
            {
                // Select a horizontal direction at random
                int horizontal = 2 * ( rand() % 2 ) - 1;
                
                // Select a vertical direction based on the type of the found pawn
                int vertical = !strcmp( board[ i ][ j ] , ChessPiece( "WP" ) ) ? -1 : 1;
                
                // Check that the new locations are within the bounds of the board
                if( !IsOnBoard( i + vertical ) || !IsOnBoard( j + horizontal ) || !IsOnBoard( 7 - i - vertical ) || !IsOnBoard( 7 - j - horizontal ) )
                {
                    // If it isn't, flip the direction of the horizontal change, and try again
                    horizontal *= -1;
                    
                    // If it's still off the board, skip it
                    if( !IsOnBoard( j + horizontal ) || !IsOnBoard( 7 - j - horizontal ) )    
                    {   continue;   }
                }
                
                // Check that this pawn shift would not put this pawn on the final rank for their type
                if( !( i + vertical > 0 ) || !( i + vertical < 7 ) )
                {   continue;   }

                // Check if space or its complement is available
                if( !SpaceOccupied( board[ i + vertical ][ j + horizontal ] ) || !SpaceOccupied( board[ 7 - i - vertical ][ 7 - j - horizontal ] ) )
                {
                    
                    // Randomly choose if the capture was done via pawn
                    if( ( rand() % 10 ) < threshold )
                    {
                        
                        // Check if there are captured pawns unaccounted for
                        if( captureCodes[ 0 ] > 0 )
                        {
                            // Check if this pawn could have captured a pawn in the pawnCodes list
                            if( !pawnCodes[ j + horizontal ] )
                            {    
                                debug ? printf( "\tSpecial Pawn Capture: %s  => %s\n" , ChessPiece( "WP" ) , ChessPiece( "BP" ) ) : ( void )0;
                                pawnCodes[ j + horizontal ] = -1;
                            }
                        }
    
                        // Check if there are captured bishops unaccounted for
                        else if( captureCodes[ 1 ] > 0 )
                        {
                            // Look through bishopCode array
                            for( int n = 0; n < 10; n++ )
                            {
                                // If the pawn is on the same color square as the bishop they tried to capture
                                if( ( (  i + j ) % 2 ) == bishopCodes[ n ] )     bishopCodes[ n ] = -1;
                            }
                        }

                        // If no more generic captures remain, then skip this pawn
                        else if( captureCodes[ 2 ] <= 0 )
                            continue;
                        
                        debug ? printf( 
                            "\t( %s  , %s  ) => ( %d%c, %d%c ) => ( %d%c, %d%c)\n", 
                            board[ i ][ j ] , board[ 7 - i ][ 7 - j ] , 
                            7 - i + 1 , ( char )( j + 65 ) , i + 1 , ( char )( 7 - j + 65 ) , 
                            7 - i + 1 - vertical , ( char )( j + horizontal + 65 ) , i + 1 + vertical , ( char )( 7 - j - horizontal + 65 ) 
                        ) : ( void )0;
                            
                        // Resets the threshold amount
                        threshold = 5;
                        
                        // Add pawns to new locations
                        board[ i + vertical ][ j + horizontal ] = !strcmp( board[ i ][ j ] , ChessPiece( "WP" ) ) ? ChessPiece( "WP" ) : ChessPiece( "BP" );
                        board[ 7 - i - vertical ][ 7 - j - horizontal ] = !strcmp( board[ 7 - i ][ 7 - j ] , ChessPiece( "WP" ) ) ? ChessPiece( "WP" ) : ChessPiece( "BP" );
                        
                        // Remove pawns from current locations ( replace with appropriate colored tile )
                        // Light = sum of coordinates is even;  ( i + j ) % 2 = 0 = false
                        // Dark = sum of coordinates is odd;    ( i + j ) % 2 = 1 = true
                        board[ i ][ j ] = ( ( i + j ) % 2 ) ? ChessPiece( "BS" ) : ChessPiece( "WS" );
                        board[ 7 - i ][ 7 - j ] = ( ( 14 - i - j ) % 2 ) ? ChessPiece( "BS" ) : ChessPiece( "WS" );
                            
                    }
                    else
                    {
                        debug ? printf( "\tPawn shift skipped.\n" ) :  ( void )0;
                        threshold++;
                    }
                    
                    // If no more captures remain, force quit the function
                    if( --numCaptured <= 0 )
                    {   return; }
                    
                    // Otherise, keep iterating
                    else
                    {   continue;   }
                }
                
                // Skips if space is occupied
                else
                {   continue;   }
            }
            
            // Skips if no pawn
            else
            {   continue;   }
        }

        // Loops back through the board until the function runs out of iterations
        if( i == 7 )
        {
            debug ? puts( "\tFull board scan complete, but iterations remain- resetting loop..." ) : ( void )0;
            i = -1;
        }    

    }


}

#pragma endregion
