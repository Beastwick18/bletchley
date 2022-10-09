#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>

int initializeSchedule( char * filename ) 
{

}

int readSchedule( char * filename )
{
  FILE * fd;

  fd = fopen( filename, "r" );
  if( fd == NULL )
  {
    printf( "Could not open schedule file: %s\n", filename ) ;
    exit( 0 ) ;
  }

  int i = 0;
  #if 0
  while ( ( fscanf ( fd, "%d%s\n", & ( si[i].time ), &( si[i].filename ) ) ) != EOF ) 
  {
    i++;
  }
  #endif
}