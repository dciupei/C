//David Ciupei
//ciupei_david@yahoo.com

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    
    if(argc < 3) {              // checks if there are 2 arguments
        fprintf(stderr, "Invalid number of arguments\n");
        return -1;
    }
    
    if(argv[1][0] != 'e' && argv[1][0] != 'd') {    //checks to see if first argument is e or d
        fprintf(stderr, "First argument must be 'e' or 'd'\n");
        return -1;
    }
    
    int e, c, n, d;
    char *phrase, EorD;
    int i = 0;
    EorD = argv[1][0];                 // sets EorD to the first arguments which is 'e' or 'd'
    phrase = argv[2];               // the phrase is the second argument
    n = strlen(phrase);             // n holds the length of the
    
    while((c = fgetc(stdin)) != EOF){       // while its not the end of the file
        
        if(c == '\n'){                  // checks for new line and puts to standard out then continues
            fputc('\n',stdout);
            continue;
        }
    
    if (EorD == 'e') {              // if encrypts
            e = (c - 32 + phrase[i % n]) % 95 + 32;             //encrypting algorithim
            fputc( e, stdout);                  // writes each character to standard out
        
    }
    else if (EorD =='d') {           // if decrypts
            d = (c - 32 - phrase[i % n] + 3 * 95) % 95 + 32;       //decrypting algorithim
            fputc( d, stdout);              // writes each character to standard out
        }
        i++;
    }
  
    return 0;
    
}



