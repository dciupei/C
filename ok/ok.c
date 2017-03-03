//David Ciupei
//CS360 Assignment #2

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define attempt 16 
#include <errno.h>


int ok(int fd, char *word){
  char buffer[attempt];
  word[attempt] = '\0';
  char *have = NULL;
  long actual;
  long top = ((lseek(fd,0,SEEK_END)/attempt)+1);    // gets the end number of strings in the file
  long bot = 0;
  // printf("%i\n", top);
    // fills the word passing through with blank spaces
  for(long i = strlen(word); i < attempt - 1; i++){
    word[i] = ' ';
  }

  word[attempt] = '\0';
  char *want = word;

  while(bot <= top){
    int mid = (bot+top)/2;          //updates the mid every iteration
    lseek(fd,mid*attempt,SEEK_SET); //set the position to the new mid


    actual = read(fd,buffer,attempt);   //read in that word
    write (fd, buffer,actual);          // writes it to the buffer
    buffer[attempt-1] = '\0';
    have = buffer;
    int comp = strcmp(want, have);      // compares the word being passed through with the file word
    if(comp == 0){
      return 1;                         //if found return 1
    }
    if(comp < 0){
      top = mid;
    }
    if(comp > 0){
      bot = mid+1;
    }
    if(bot >= top){                     // if no more words to search for
      return 0;
    }

  }

  return 0;
}

int main(int argc, char* argv[]) {

  int fd =0;
  char word[attempt];
    // checks to see if a word is being passed through
  if (!argv[1]){
    fprintf(stderr, "Error: No word inputed for searching!\n");
    exit(1);
  } else{
    strcpy(word, argv[1]);
  }
  fd = open ("webster", O_RDONLY,0);        // opens the webster file for reading
 
    //checks if the file can be opened
  if(fd < 0){
    fprintf(stderr, "Error: %s: Can't open %s for reading -- %s\n", argv[0],"webster",strerror (errno));
    exit(1);
  }
  
  word[attempt-1] = '\0';
    //passes the word and file through method "ok" and returns 0 or 1 if its found
  int result = ok(fd, word);

  if(result == 1){
    printf("YES\n");
  }else{
    printf("NO\n");
    }

  close (fd);
  return 0;
}
