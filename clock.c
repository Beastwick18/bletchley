#include "clock.h"
#include <signal.h>
#include <string.h>
#include <stdio.h>

static pthread_t clock_tid ;
static sigset_t signal_set ;
static int clockNotRunning ;

int interval = DEFAULT_INTERVAL ;
struct notify_list * participants_head = NULL ;

static void handleAlarm (int sig )
{

  if( clockNotRunning ) return;

  // Notify participants
  struct notify_list * list = participants_head ;
  while( list ) 
  {
    list->tick();
    list = list -> next ;
  }
  alarm(ONE_SECOND);
}

void * clock_thread ( void * args )
{
  int sig;
  sigwait( & signal_set, & sig );
}

int initializeClock( int _interval ) 
{
  interval = _interval ;
  clockNotRunning = 1 ;

  sigemptyset( & signal_set );
  sigaddset  ( & signal_set, SIGALRM );

}

void startClock ( ) 
{

  struct sigaction act;
 
  // Zero out the sigaction struct
  memset (&act, '\0', sizeof(act));
 
  // Set the handler to use the function handle_alarm()
  act.sa_handler = & handleAlarm;
 
  // Install the handler and check the return value.
  if (sigaction(SIGALRM, &act, NULL) < 0) {
    perror ("sigaction: ");
    return ;
  }
  alarm( ONE_SECOND ) ; 

  clockNotRunning = 0 ;

  pthread_create( &clock_tid, NULL, clock_thread, NULL ) ;

}

void stopClock ( ) 
{
  clockNotRunning = 1 ;
  while( participants_head ) 
  {
    struct notify_list * entry = participants_head;
    participants_head = participants_head -> next ;
    free( entry ) ;
  } 
  pthread_cancel( clock_tid );
  pthread_join( clock_tid, NULL );
}

void registerWithClock( void * ( * tick ) ( void ) )
{
    // Add a new entry to the list of partificpants wanting
    // to be notified
    struct notify_list * list = participants_head ;
    if( participants_head == NULL )
    {
      struct notify_list * new_entry = ( struct notify_list * ) malloc( sizeof( struct notify_list ) ) ;
      new_entry -> tick = tick ;
      new_entry -> next = NULL;
      participants_head = new_entry;
      return ;  
    }

    while( list && list->next != NULL ) 
    {
        list = list -> next ;
    }

    struct notify_list * new_entry = ( struct notify_list * ) malloc( sizeof( struct notify_list ) ) ;
    new_entry -> tick = tick ;
    new_entry -> next = NULL;
    list = new_entry;
    return ;  
}