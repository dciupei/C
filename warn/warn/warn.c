//David Ciupei
//CS360 Assignment #5

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <ctype.h>
#include <assert.h>

int rdr,wtr,pCode,DELAY;
char buf[256];
static char *string = NULL;

void parent(int c){
    signal(SIGINT, SIG_IGN);
    if(c == SIGINT){

        kill(pCode, SIGFPE);    //send signal

        printf("\nEnter a phrase: ");
        fgets(buf, 256, stdin);         //gets the string and puts in buffer
        write(wtr, buf, 256);

    
        if(strcmp(buf, "exit\n")==0){
            kill(pCode, SIGFPE);
            exit(0);
        }
    
    }


}

void child(int c){
    signal(SIGINT, SIG_IGN);
   
    if(c == SIGINT){
        signal(SIGALRM, SIG_IGN);
    }else if(c == SIGFPE){
            read(rdr, buf, 256);
            if (strcmp(buf, "exit\n")==0){      //exits program if found "exit"
                printf("Program is exiting...\n\n");
                exit (0);
            }
            DELAY = (int)strtol(buf, &string, 10);  //gets number to delay printing
            if(DELAY == 0){ //if no number specified set to 5
                DELAY = 5;
            }

            if(string[0] == ' '){ // gets rid of space after number is gotten
                string++;
            }
            printf("%s\n", string);
            alarm(DELAY);
            signal(SIGALRM, child);
    }else if(c == SIGALRM){         //repeats until SIGFPE is detected
        printf("%s\n", string);
        alarm(DELAY);
    }

}



int main(int argc, const char * argv[]) {
    int fd[2];

    pipe(fd);
    assert (pipe (fd) >= 0);
    rdr = fd[0];
    wtr = fd[1];

    if((pCode = fork())){
        close(rdr);
        while(1){
            signal(SIGINT, parent); //sends a signal to parent
            pause();
        }
    }else{
        close(wtr);
        while (1) {
            signal(SIGFPE, child); //sends signal to child
            signal(SIGINT, child); //sends signal to child

            pause();

        }

    }
    
    return 0;
}
