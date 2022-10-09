#ifndef __SCHEDULE_H___
#define __SCHEDULE_H___

#define MAX_SCHEDULE_FILENAME_SIZE 10
#define MAX_TIME_DIGITS 4

int scheduleCount = 0 ;

struct schedule_item 
{
  int time ;
  char * filename ;
} schedule_item ;

struct schedule_list
{
  struct schedule_item * message ;
  struct schedule_list * next ;
} ;

int initializeSchedule( char * filename ) ;

int freeSchedule( void ) ;

int readSchedule( char * filename ) ;

#endif