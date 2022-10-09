#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include "../include/crypto.h"

int main( int argc, char *argv[] )
{
  DIR * FD ;
  struct dirent * in_file ;
  char   buffer[BUFSIZ] ;

  if ( NULL == ( FD = opendir ( argv[1] ) ) ) 
  {
    fprintf( stderr, "Error : Failed to open input directory - %s\n", strerror( errno ) ) ;
    return 1 ;
  }

  while ( ( in_file = readdir( FD ) ) ) 
  {
    if ( !strcmp ( in_file->d_name, "." ) )
      continue ;

    if ( !strcmp ( in_file->d_name, ".." ) )    
      continue ;

 
    int input_filename_length = strlen( argv[1] ) + strlen( in_file->d_name ) + strlen( ".enc" ) ;
    int output_filename_length  = strlen( argv[2] ) + strlen( in_file->d_name ) ;

    char * input_filename = ( char * ) malloc ( sizeof( char ) + input_filename_length ) ;
    memset( input_filename, 0, sizeof( char ) + input_filename_length );

    char * output_filename = ( char * ) malloc ( sizeof( char ) + output_filename_length ) ;
    memset( output_filename, 0, sizeof( char ) + output_filename_length );

    strncpy( input_filename, argv[1], strlen( argv[1] ) ) ;
    strcat ( input_filename, in_file->d_name );

    strncpy( output_filename, argv[2], strlen( argv[2] ) ) ;
    strcat ( output_filename, in_file->d_name );
    output_filename[ strlen( output_filename ) - 4 ] = '\0';

    printf("Decrypting %s to %s\n", input_filename, output_filename ) ;
    decryptFile( input_filename, output_filename );

    free( input_filename ) ;
    free( output_filename ) ;
  }

  return 0 ;
}
