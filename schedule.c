#include "schedule.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static struct schedule_list * schedule ;

int initializeSchedule( char * filename ) 
{
  schedule = NULL ;
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
    int entry_time = atoi( time_string ) ;

    struct schedule_item * item = ( struct schedule_item * ) malloc ( sizeof(struct  schedule_item ) );
    struct schedule_list * list_entry =  ( struct schedule_list * ) malloc ( sizeof( struct schedule_list ) );

    item -> filename = ( char * ) malloc ( sizeof( char ) * MAX_SCHEDULE_FILENAME_SIZE ) ;
    item -> time = entry_time ;
    strncpy( item -> filename, filename, MAX_SCHEDULE_FILENAME_SIZE ) ;

    list_entry -> message = item ;
    list_entry -> next = NULL ;

    struct schedule_list * list  = schedule ; 
    if( schedule == NULL )
    {
      schedule = list_entry ; 
    }
    else
    {
      while( list && list->next != NULL )
      {
        list = list -> next ;
      }
      list -> next = list_entry ;
    }

  }
  fclose( fd ) ;

  free( time_string ) ;
  free( filename ) ;
}

int freeSchedule( void )
{
  while( schedule )
  {
    struct schedule_list * node = schedule ; 

    free( schedule -> message -> filename ) ;
    free( schedule -> message ) ;
    
    schedule = schedule -> next ;

    free( node );
  }
  return 0 ;
}