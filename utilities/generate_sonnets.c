#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEBUG 
#define WHITESPACE " \t\n"

int main( int argc, char * argv[] )
{
  FILE *fd ;

  fd = fopen( argv[1], "r") ;
 
  if (NULL == fd) 
  {
    printf("File can't be opened \n") ;
  }

  char * buffer = ( char * ) malloc( 255 ) ;
 
  fgets( buffer, 3, fd ) ;   
  //fgets( &buffer[0], 255, fd ) ;   
  //fwrite( buffer, 1, strlen( buffer ), ofp );


  int i;
  for( i = 0 ; i < 145; i ++ )
  {
    buffer = strsep( &buffer, WHITESPACE ) ;

    char * filename = (char*) malloc ( 255 ) ;
    strcat( filename, buffer ) ;
    strcat( filename, ".txt" ) ;

    FILE *ofp = fopen( filename, "w" ); 
    memset( filename, 0, 255 ) ;
    fgets( &buffer[0], 255, fd ) ; 
    fwrite( buffer, 1, strlen( buffer ), ofp );
    fgets( &buffer[0], 255, fd ) ; 
    fwrite( buffer, 1, strlen( buffer ), ofp );
    while( strlen( buffer ) != 2 && strlen( buffer ) != 3 && strlen( buffer ) != 4 )
    {
      fwrite( buffer, 1, strlen( buffer ), ofp );
      fgets( &buffer[0], 255, fd ) ; 
    }
    fclose( ofp ) ;
    free( filename ) ;
  }
             
  fclose( fd ) ;

  free( buffer ) ;

  return 0 ;
}
