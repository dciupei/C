// David Ciupei
// CS 261
// Assignment #5

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include "hash.h"
#define _POSIX_C_SOURCE 200809L
#define MAX_WORD_SIZE 256



struct LList {                              // linked list
    int counter;                            // counter for the word
    char word[MAX_WORD_SIZE];               // word with the max word size
    struct LList *next;                     // pointer to the next word
};


char* getNextWord(FILE* fd){
    assert(fd != NULL);                     //checks if the file is not empty
    
    char ch;
    while ((ch = fgetc(fd)) != EOF) {       // this will get the next character from the file as long as it doesnt reach the end of the file
        if (isalnum(ch)) break;             // checks if the passed character is alphanumeric
        
        
    }
    if (ch == EOF)return NULL;              // if the character is the end of the file return null
    
    char wordBuffer[MAX_WORD_SIZE];         //array with the MAX_WORD_SIZE in the array
    int pos = 0;
    
    wordBuffer[pos++] = tolower(ch);        //changes each word in the file to lowercase letter
    
    while((ch = fgetc(fd)) != EOF){         //gets the character from the file
        if (isspace(ch) || pos >= MAX_WORD_SIZE - 1)break;  //if there is white space or if the word doesnt exceed 256
        
        if (isalnum(ch)){                   // if the passed character is alphanumeric
            wordBuffer[pos++] = tolower(ch); // changes the word to lowercase
        }
    }
    wordBuffer[pos] = '\0';                 // terminates the string from the list
    char* result = (char*) malloc(strlen(wordBuffer)+1); // allocates memory of the list of words and puts it in result /
    strcpy(result,wordBuffer);              // copies the wordbuffer array to the result
    
    return result;                          // returns the words
}



void addWord (struct LList **list, char * w) {
    assert (list);                          //checks to see if there is a list
    struct LList *temp = *list;             //sets a temporary pointer
    
    while (temp) {                          //while the temp is true
        if (strcmp(temp->word, w) == 0) {   // compares the temp word from LList to the word from the file to see if they are the same
            temp->counter+=1;               // increments the count by 1 if true
            return;
        }
        temp = temp->next;                  //increments to the next word in the list
    }
    
    temp = (struct LList *)malloc (sizeof(struct LList)); //allocates memory for the list with temp being the pointer
    temp->next = *list;                     //the next word of the temp is the next word pointed from the file
    strcpy(temp->word, w);                  //copies the temp word with the word being passed in
    temp->counter=1;                        //sets the count of the word that only occurs once to 1
    *list = temp;                           //the list pointer is set to the the temp
    return;
    
}

int compfunc( const void* node1, const void* node2){
    //changes from void* to Node**
  Node** anode1 = (Node**) node1;
  Node** bnode2 = (Node**) node2;
    //dereferences the Node** to Node*
  Node* Fnode1 = *anode1;
  Node* Fnode2 = *bnode2;
    // changes it to an int* and sets the first node to a and second to b
  int  a = (int)Fnode1->val;
  int  b = (int)Fnode2->val;
    // if the first node is greater then the second returns -1
  if (a>b){
      return -1;
}
    //if they are equal returns 0
  if (a==b){
      return 0;
}
    //else returns 1
  return 1;
}

// this will print out the content of the sorted words of the table
void printFreq(HashTable* table, int printNum){
  if (printNum == 0){
    printNum = table->Entries;      // if the print number is equal to 0 it sets it to the table->Entries
  }
  Node** List;
  List = Array(table);                //makes an array of the elements in the table
  qsort(List,(table->Entries-1),sizeof(Node*),compfunc); // calls on qsort to arrange the words by there count
  for (int i = 0; i < printNum; i++){       // prints the contents with the number inputed by the user being the limit
    Node* node = List[i];
    printf("Key: %s   Value: %d\n", node->key,(int)node->val);
 }
  HashFree(table);      // frees the hashtable
}

// the function that is passed through the hashapply method
void printTable(Node* node, int x){
    printf("Key: %s  Value: %d\n",node->key,(int)node->val);

}



int main(int argc, char* argv[]){
    if (argc < 2){
        fprintf(stderr, "Error: %s Expecting at least one filename.\n", argv[0]);
        exit(1);
    }
    int printNum = 0;
    for (int i = 1; i <argc; i++){
      if (strncmp(argv[i],"-",1) == 0){     // if there is a number inputed by the user
	sscanf(argv[i],"-%d", &printNum);       //gets the number and stores it in printNum
	break;
	
      }

    }
    char* fileWord;                       // a pointer to the word in the file
    void* value;                          // this will contain the value of the key
    HashTable* table = HashInit(10);      // initialize the hashtable with 10 buckets
    
    for (int i = 1; i < argc; i++) {
      if (strncmp(argv[i],"-",1)!=0){           // if there is no number inputed by user
        FILE* fd = fopen(argv[i], "r");             //opens the file for reading
        if(fd == NULL) {
            fprintf(stderr, "Can't open file %s\n, argv[1]", argv[i]);      //if error prints out message
            exit(1);
        }
	if (fd != NULL){                         // if there is a file with content prints a message
	  printf ("File Exits!\n");
	  printf("Here is the contents:\n");
	  printf("\n");
	}
    while((fileWord = getNextWord(fd)) != NULL) {
            value = HashSearch(table, fileWord);           //searches for the key and returns the value
            if(value != NULL) {
                value++;
                HashInsert(table, fileWord, value);         //inserts the value found with the key in the table
            }
            else {
                HashInsert(table, fileWord, (int*) 1);      // if new the key will get a value of 1
            }
        }
            fclose(fd);
      }
    }

    printFreq(table,printNum);           //prints the contents of the array
 // HashApply(table,printTable);        //passes through the hashapply to be printed
    
    return 0;
}

