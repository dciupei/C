//David Ciupei
//CS460 Project #2
//SID:11383576

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <unistd.h>
#include "buffer.h"


buffer_item buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty, full;

int count;
int SIGNAL;

void sig_handler (int signo) {
  if (signo == SIGINT) {
    printf(" received SIGINT and going to finish in the time entered!\n");
    SIGNAL = 1;
  }
}


int insert_item (buffer_item item){
  if (count < BUFFER_SIZE) {
    buffer[count] = item;
    count++;
    return 0;
  } 
  else{
  	return -1;

  }
}


int remove_item (buffer_item *item){
  if (count > 0) {
    *item = buffer[count - 1];
    count--;
    return 0;
  }
  else{
    return -1;
  }
}

void *producer (void *param){
  buffer_item item;

  while (1) {
    signal(SIGINT, sig_handler);

    /* sleep for a random period of time */
    sleep(rand() % 10 + 1);

    /* generate a random number */
    item = rand();
    sem_wait(&empty);
    pthread_mutex_lock(&mutex); 

    if (insert_item(item))
      fprintf(stderr, "report error condition\n");
    else
      printf("producer produced %d\n",item);

    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }

}

void *consumer (void *param){
  buffer_item item;

  while (1){
    signal(SIGINT, sig_handler);

    /* sleep for a random period of time */
    sleep(rand() % 10 + 1);

    sem_wait(&full);
    pthread_mutex_lock(&mutex);

    if ( remove_item(&item) )
      fprintf(stderr, "report error condition\n");
    else
      printf("consumer consumed %d\n",item);

    pthread_mutex_unlock(&mutex);
    sem_post(&empty);

    if (SIGNAL){
      break;
    }
  }
}

int main (int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Not enough arguments!\nNeed 3 numbers!\n");
    return -1;
  }

  
  int time = atoi( argv[1] );  
  int producers = atoi( argv[2] );  
  int consumers = atoi( argv[3] );

  count = 0;
  SIGNAL = 0;

 
  pthread_mutex_init( &mutex, NULL );
  sem_init( &empty, 0, BUFFER_SIZE );
  sem_init( &full, 0, 0 );

  pthread_t thread1;	//Producer thread
  pthread_t thread2;    //Consumer thread

  pthread_attr_t attr;
  pthread_attr_init(&attr);


  
  int i;
  for (i = 0; i < producers; ++i) {
    pthread_create(&thread1, &attr, producer, NULL);
  }

  for (i = 0; i < consumers; ++i) {
    pthread_create(&thread2, &attr, consumer, NULL);
  }

  pthread_join(thread2, NULL);


  sleep(time);
  exit(0);
}
