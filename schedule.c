#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>

static struct schedule_list * schedule = NULL ;

int initializeSchedule( char * filename ) 
{
  readSchedule( filename ) ;
}

int readSchedule( char * schedule_file )
{
  FILE * fd;

  fd = fopen( schedule_file, "r" );
  if( fd == NULL )
  {
    printf( "Could not open schedule file: %s\n", schedule_file ) ;
    exit( 0 ) ;
  }

  int i = 0;

  char * time_string = ( char * ) malloc( sizeof( char ) * MAX_TIME_DIGITS ) ;
  char * filename = ( char * ) malloc ( sizeof( char ) * MAX_SCHEDULE_FILENAME_SIZE ) ;

  while ( fscanf ( fd, "%s%s\n", time_string, filename ) != EOF ) 
  {
    printf("%s %s\n", time_string, filename ) ;
    int entry_time = atoi( time_string ) ;

    struct schedule_item * item = ( struct schedule_item * ) malloc ( sizeof(struct  schedule_item ) );
    struct schedule_list * list_entry =  ( struct schedule_list * ) malloc ( sizeof( struct schedule_list ) );

    list_entry -> message = item;

    struct schedule_list * list  = schedule ; 
    if( schedule = NULL )
    {
      schedule = list_entry ;
    }
    else
    {
      while( list )
      {
        list = list -> next ;
      }
      list = list_entry ;
    }

  }

  fclose( fd ) ;

  free( time_string ) ;
  free( filename ) ;
}