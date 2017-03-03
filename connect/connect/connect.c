//David Ciupei
//CS360 Assignment #4

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    int i = 0;	/* i=1, 2, ..., n */
    int n = 0;
    int c = 0;  // colon
    int fd[2];	/* pipe file descriptors */
    int rdr, wtr;  	/* fd[0] and fd[1] */
    char text[10]; 	/* "*6" etc. */
    
    assert (pipe (fd) >= 0);
    rdr = fd[0]; wtr = fd[1];
    
    if(argc < 2){
        fprintf(stderr, "No input was inputted!\n");
        exit(1);
    }
    
    while (i < argc){
        if(i == 1){
            if(strcmp(argv[i],":") == 0){
                fprintf(stderr, "No first argument was found!\n");
                exit(1);
            }
            i++;
            continue;
        }
        if(strcmp(argv[i],":") == 0){
            c = i;
            break;
        }
        if(i == argc-1){
            if(strcmp(argv[i],":") != 0){
                fprintf(stderr, "No colon was found!\n");
                exit(1);
            }
        }
        i++;
    }
    
    if(argv[c+1] == NULL){
        fprintf(stderr, "No argument after colon was found!\n");
        exit(1);
    }
    
    argv[c] = NULL;
    
    if (fork ()) { /* parent writes ... */
        
        close (wtr);
        close (0); dup (rdr); close (rdr);
        execlp (argv[c+1], *(argv+c+1),0);
        fprintf (stderr, "%s: exec failed\n", argv[0]);
        exit (1);
    
      
        
    
    } else { /* child reads ... */
     
        close (rdr);
        write (wtr, "1", 1);
        for (i = 2; i <= n; ++i) {
            sprintf (text, "*%d", i);
            write (wtr, text, strlen (text));
        }
        write (wtr, "\n", 1);
        close(1); dup(wtr); close (wtr);
        execlp (argv[1], *(argv+1),0);
        exit (0);
        
    }
    return 0;
}


