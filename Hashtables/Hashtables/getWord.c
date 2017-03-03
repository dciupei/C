//
//  main.c
//  Hashtables
//
//  Created by David Ciupei on 1/28/16.
//  Copyright © 2016 David Ciupei. All rights reserved.
//


#define  _GNU_SOURCE
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
//#include "getWord.h"
#include "hashtable.h"
#define DICT_MAX_WORD_LEN 256

/* Reads characters from fd until a single word is assembled */
/* and returns a copy of the word allocated from the heap.   */
/* NULL is returned at EOF. */
/* Words are defined to be separated by whitespace and start */
/* with an alphabetic character.  All alphabetic characters  */
/* translated to lower case and punctuation is removed.      */

char* getNextWord(FILE* fd) {
    char ch;/* holds current character */
    char wordBuffer[DICT_MAX_WORD_LEN];/* buffer for build a word */
    int putChar = 0;/* current pos in buffer   */
    
    assert(fd != NULL);/* the file descriptor better not be NULL */
    
    /* read characters until we find an alphabetic one (or an EOF) */
    while ((ch = fgetc(fd)) != EOF) {
        if (isalpha(ch)) break;
    }
    if (ch == EOF) return NULL;/* if we hit an EOF, we're done */
    
    /* otherwise, we have found the first character of the next word */
    wordBuffer[putChar++] = tolower(ch);
    
    /* loop, getting more characters (unless there's an EOF) */
    while ((ch = fgetc(fd)) != EOF) {
        /* the word is ended if we encounter whitespace */
        /* or if we run out of room in the buffer       */
        if (isspace(ch) || putChar >= DICT_MAX_WORD_LEN - 1) break;
        
        /* otherwise, copy the (lowercase) character into the word   */
        /* but only if it is alphanumeric, thus dropping punctuation */
        if (isalnum(ch)) {
            wordBuffer[putChar++] = tolower(ch);
        }
    }
    
    wordBuffer[putChar] = '\0';/* terminate the word          */
    return strdup(wordBuffer); /* re-allocate it off the heap */
}

int compfunc( const void* node1, const void* node2){
    KVpair** anode1 = (KVpair**) node1;
    KVpair** bnode2 = (KVpair**) node2;
    KVpair* Fnode1 = *anode1;
    KVpair* Fnode2 = *bnode2;
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
    return 1;
}

// the function that is passed through the hashapply method
void printTable(KVpair* node, int x){
    printf("Key: %10s  Value: %d\n",node->key,(int)node->val);
    
}

void StoreWord(HT* table, char* curr){
    void* value = malloc(sizeof(void*));
    value = 1;
    void* temp = malloc(sizeof(void*));
    temp = HashSearch(table, curr);
    if(temp != NULL){
        temp++;
        HashInsert(table, curr, temp);

    }else{
        HashInsert(table, curr, value);
    }
}


int main(int argc, char * argv[]) {
    
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
    
    char* fileWord1 = (char*)malloc(sizeof(char*));
    char* fileWord2 = (char*)malloc(sizeof(char*));
    HT* table = HashInit(10);      // initialize the hashtable with 10 buckets

    for (int i = 1; i < argc; i++) {
        if (strncmp(argv[i],"-",1)!=0){           // if there is no number inputed by user
            FILE* fd = fopen(argv[i], "r");             //opens the file for reading
            if(fd == NULL) {
                fprintf(stderr, "Can't open file %s\n, argv[1]", argv[i]);      //if error prints out message
                exit(1);
            }
            
            fileWord1 = getNextWord(fd);
            char* space = " ";
            while(fileWord1 != NULL) {
                fileWord2 = getNextWord(fd);

                if(fileWord2  == NULL){     // if EOF breaks from while loop
                    break;
                }
        
                strcat(fileWord1, space);
                strcat(fileWord1, fileWord2);
                
                StoreWord(table, fileWord1);
           
                fileWord1 = fileWord2;
            }
            fclose(fd);
            free(fileWord1);
            free(fileWord2);
        }

    }
    
    KVpair** List;
    List = Array(table);                //makes an array of the elements in the table
    qsort(List,(table->count-1),sizeof(KVpair*),compfunc); // calls on qsort to arrange the words by there count
    HashApply(table,List,printNum, printTable);
    HashFree(table);
    return 0;
}
