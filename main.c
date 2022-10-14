#include "include/crypto.h"
#include "schedule.h"
#include <pthread.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "clock.h"

#define MAX_NUM_THREADS 1024 
#define MAX_FILENAME_LENGTH 255
#define BUFFER_SIZE 148

static char * message_buffer[BUFFER_SIZE];
static int count ;
static int running = 1 ;

pthread_t message_receiver_tid ;
pthread_t decryptor_tid[ MAX_NUM_THREADS ] ;

pthread_mutex_t message_lock;
// pthread_mutex_t count_lock;

static void handleSIGUSR2( int sig )
{
  printf("Time to shutdown\n");
  running = 0 ;
}

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
  strncpy( message, message_buffer[count-1], MAX_FILENAME_LENGTH ); 
  count--;

  return 0;
}

static void * tick ( void ) 
{
   return NULL ;
}

void * receiver_thread( void * args )
{
  while( running )
  {
    pthread_mutex_lock(&message_lock);
    char * message_file = retrieveReceivedMessages( );

    if( message_file )
    {
      // pthread_mutex_lock(&count_lock);
      insertMessage( message_file ) ;
      // pthread_mutex_unlock(&count_lock);
    }
    
    pthread_mutex_unlock(&message_lock);
  }
}

void * decryptor_thread( void * args )
{
  while( running )
  {
    if(count <= 0)
      continue;
    char * input_filename  = ( char * ) malloc ( sizeof( char ) * MAX_FILENAME_LENGTH ) ;
    char * output_filename  = ( char * ) malloc ( sizeof( char ) * MAX_FILENAME_LENGTH ) ;
    char * message = ( char * ) malloc ( sizeof( char ) * MAX_FILENAME_LENGTH ) ;

    memset( message,         0, MAX_FILENAME_LENGTH ) ;
    memset( input_filename,  0, MAX_FILENAME_LENGTH ) ;
    memset( output_filename, 0, MAX_FILENAME_LENGTH ) ;

    pthread_mutex_lock(&message_lock);
    if(count <= 0) {   
      free( input_filename );
      free( output_filename );
      free( message );
      pthread_mutex_unlock(&message_lock);
      continue;
    }
    // pthread_mutex_lock(&count_lock);
    removeMessage( message );
    // pthread_mutex_unlock(&count_lock);
    
    pthread_mutex_unlock(&message_lock);

    strncpy( input_filename, "ciphertext/", strlen( "ciphertext/" ) ) ;
    strcat ( input_filename, message );

    strncpy( output_filename, "results/", strlen( "results/" ) ) ;
    strcat ( output_filename, message );
    output_filename[ strlen( output_filename ) - 8 ] = '\0';
    strcat ( output_filename, ".txt" );

    decryptFile( input_filename, output_filename );
    free( input_filename ) ;
    free( output_filename ) ;
    free( message ) ;
  }
}

int main( int argc, char * argv[] )
{
    if( argc != 2 )
    {
      printf("Usage: ./a.out [number of threads]\n") ;
      return 0;
    }
    int num_threads = atoi( argv[1] ) ;
    pthread_t tid[ MAX_NUM_THREADS ] ;

    // Create mutex for message_buffer so that we can
    // lock and unlock it. This will prevent sequential
    // read/modification of message_buffer.
    if(pthread_mutex_init(&message_lock, NULL) != 0)
    {
      fprintf(stderr, "Couldn't create mutex");
      return EXIT_FAILURE;
    }
    // if(pthread_mutex_init(&count_lock, NULL) != 0)
    // {
    //   fprintf(stderr, "Couldn't create mutex");
    //   return EXIT_FAILURE;
    // }
    
    // initialize the message buffer
    int i ;
    for( i = 0; i < BUFFER_SIZE; i++ )
    {
      message_buffer[i] = ( char * ) malloc( MAX_FILENAME_LENGTH ) ;
    }

    count = 0 ;

    struct sigaction act;
    memset ( & act, '\0', sizeof( act ) ) ;
    act . sa_handler = & handleSIGUSR2 ;

    if ( sigaction( SIGUSR2, &act, NULL ) < 0 )  
    {
      perror ( "sigaction: " ) ;
      return 0;
    }

    initializeClock( ONE_SECOND ) ;
    registerWithClock( tick ) ;

    initializeSchedule( "schedule.txt" ) ;

    pthread_create( &message_receiver_tid, NULL, receiver_thread, NULL ) ;

    for( i = 0; i < num_threads; i++ )
    {
      pthread_create( & decryptor_tid[i], NULL, decryptor_thread, NULL ) ;
    }

    startClock( ) ;

    while( running ) ;

    stopClock( ) ;

    pthread_join( message_receiver_tid, NULL ) ;

    for( i = 0; i < num_threads; i++ )
    {
      pthread_join( decryptor_tid[i], NULL ) ;
    }

    for( i = 0; i < BUFFER_SIZE; i++ )
    {
      free( message_buffer[i] ) ;
    }
    freeSchedule( ) ;
    pthread_mutex_destroy(&message_lock);
    // pthread_mutex_destroy(&count_lock);

    return 0 ;
}
