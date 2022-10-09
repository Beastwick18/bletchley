#ifndef __SCHEDULE_H___
#define __SCHEDULE_H___

#define MAX_SCHEDULE_FILENAME

int scheduleCount = 0 ;

struct schedule_item
{
  int time ;
  char * filename ;
} ;

typedef struct schedule 
{
  struct schedule_item message ;
  struct schedule_item * next ;
} schedule ;

int initializeSchedule( char * filename ) ;

int readSchedule( char * filename ) ;

#endif