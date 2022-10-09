#include "include/crypto.h"
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "clock.h"

#define MAX_NUM_THREADS 10 
#define MAX_FILENAME_LENGTH 255
#define BUFFER_SIZE 1

char * message_buffer[BUFFER_SIZE];
int count ;



int insertMessage( char * message )
{
  assert( count < BUFFER_SIZE && "Tried to add a message to a full buffer");

  strncpy( message_buffer[count] , message, MAX_FILENAME_LENGTH ); 
  count++;
  
  return 0;
}

int removeMessage( char *message )
{
  assert( count && "Tried to remove a message from an empty buffer");
  strncpy( message, message_buffer[count], MAX_FILENAME_LENGTH ); 
  count--;

  return 0;
}

void * tick ( void ) 
{
   printf("Tick!\n") ;
   return NULL ;
}

int main( int argc, char * argv[] )
{
    pthread_t tid[ MAX_NUM_THREADS ] ;
    pthread_t message_generator ;

    // initialize the message buffer
    int i ;
    for( i = 0; i < BUFFER_SIZE; i++ )
    {
        message_buffer[i] = ( char * ) malloc( MAX_FILENAME_LENGTH ) ;
    }

    count = 0 ;

    initializeClock( ONE_SECOND ) ;
    registerWithClock( tick ) ;

    startClock( ) ;
    stopClock( ) ;

    for( i = 0; i < BUFFER_SIZE; i++ )
    {
        free( message_buffer[i] ) ;
    }

    return 0 ;
}
