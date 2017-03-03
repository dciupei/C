//David Ciupei
//CS360 Assignment #7

#include <stdlib.h>
#include <math.h>
#include "random_r.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define chopsticks 5

pthread_mutex_t chopS[chopsticks];
unsigned int state[5] = {0,1,2,3,4};



int Thinking(int totalT, int philosopher){    //calculates the amount of thinking time each philosopher spent
    int thinkmean = 11;
    int thinkingstdev = 7;

    int think = randomGaussian_r(thinkmean, thinkingstdev, &state[philosopher]);

    if(think < 0){         // if thinking negative set to 0
        think = 0;
    }
    
    printf("philosopher %d thinking for %d seconds. (total = %d)\n", philosopher, think, totalT);
    totalT += think;

    sleep(think);

    return totalT;
    
}

int Eating(int totalE, int philosopher){ //calculates the amount of eating time each philosopher spent
    int eatingmean = 9;
    int eatingstdev = 3;

    int eat = randomGaussian_r(eatingmean, eatingstdev, &state[philosopher]);
    
    if(eat < 0){        // if eating negative set to 0
        eat = 0;
    }
    
    printf("philosopher %d eating for %d seconds. (total = %d)\n", philosopher, eat, totalE);
    totalE += eat;
    sleep(eat);
    return totalE;
}


void philo(int philosopher){
    int thinking = 0;
    int finishEating = 0;
    int count = 1;
    thinking = Thinking(thinking, philosopher);      //gets the thinking time of each philosopher

    
    while (finishEating < 100){

        while (count){
            pthread_mutex_lock(&chopS[philosopher]);

            if (pthread_mutex_trylock(&chopS[(philosopher + 1) % chopsticks]) == EBUSY){
                pthread_mutex_unlock(&chopS[philosopher]);
                count = 1;
            }else{
                count = 0;
            }
    }

        finishEating = Eating(finishEating, philosopher);    //sees how much each philosopher will eat

        pthread_mutex_unlock(&chopS[philosopher]);
        pthread_mutex_unlock(&chopS[(philosopher + 1) % chopsticks]);
        
        thinking = Thinking(thinking, philosopher);      //gets the thinking time of each philosopher
        
    }
    
    if(finishEating >= 100){
        printf("philosopher %d has left the table and ate for %d seconds.\n", philosopher, finishEating);
    }
}



int main(int argc, const char * argv[]) {
    int philosopher = 0;
    pthread_t philos[5];

    for (int i = 0; i < 5; i++){
        pthread_mutex_init(&chopS[i], NULL);    
    }
    
    while(philosopher < 5){     //goes through the 5 philosophers
        pthread_create(&philos[philosopher], NULL, (void*) philo, (void*) philosopher);
        philosopher++;
    }
    
    
    for(int i = 0; i < 5; i++){
        pthread_join(philos[i], NULL);
    }

    printf("\nPhilosophers have finished eating.\n\n");
    

    return 0;
}
