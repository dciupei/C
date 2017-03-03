//
//  hashtable.c
//  Hashtables
//
//  Created by David Ciupei on 1/28/16.
//  Copyright © 2016 David Ciupei. All rights reserved.
//

#include "hashtable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>


float HashLoadfactor(HT* table){
    return (float)((table->count)/(table->size));
}

int Hash(char* key){
    
    int hashvalue = 0;
    char *p = key;
    for (int i = 0;i<strlen(key);i++){
        hashvalue = (33 * hashvalue)+p[i];
        
    }
    if (hashvalue < 0){return -hashvalue;}
    return hashvalue;
    
}

//this Initializes the hash table
HT* HashInit(int buckets){
    HT* table;
    if((table = malloc(sizeof(HT)))==NULL){  //makes room for the table
        return NULL;
    }
    // allocates memory for the LL.
    if((table->table = malloc(buckets*sizeof(KVpair*)))== NULL){
        return NULL;
    }
    for(int i = 0; i<buckets; i++){
        table->table[i]=NULL; // fills the spots with Null with how many buckets there are
    }
    table->size = buckets;  // the size of the table is the amount of buckets
    table->count = 0;
    return table;
}

void checkTable(HT*table){
    if((HashLoadfactor(table)) >= 0.7){                     //checks to see how full the table is
        printf ("Table is getting full. Needs to be rehashed\n");
        HashRehash(table);                                  // rehashes if needed to
    }
}

void insertNode(HT* table, KVpair* LLNode, int location,char* key,void* val){
    LLNode = table->table[location];
    KVpair* newN = (KVpair*)malloc(sizeof(KVpair));
    newN->key =key;
    newN->val = val;
    newN->next = LLNode;
    table->table[location] = newN;
    table->count++;
}

int HashInsert(HT* table,char* key,void* val){
    assert(key != NULL);
    assert(val != NULL);
    checkTable(table);
    int location = (int)Hash(key) % table->size;
    KVpair* LLNode = table->table[location];
    //linked list is empty, put new entry in the first spot.
    if (LLNode == NULL) {
        insertNode(table, LLNode, location, key, val);

    }else{
        while (strcmp(LLNode->key,key)!= 0){
            LLNode = LLNode->next;
            if (LLNode==NULL){
                LLNode = table->table[location];
                insertNode(table, LLNode, location, key, val);
            }
        }
        LLNode->val = val;
    }
  
    return 0;
    
}


static void HashRehash(HT* table){
    printf("new size will be: %i\n",(int)(table->size)*3);
    HT* newtable = HashInit((table->size)*3);  //triple the table size.
    KVpair* Current = NULL;
    for ( int i = 0; i < table->size; i++ ) {
        Current = table->table[i];
        while (Current != NULL) {
            HashInsert ( newtable, Current->key, Current->val );
            Current = Current->next;
        }
    }
    free(Current);
    free(table->table);
    *table = *newtable;
}



//this searches the table checking if the key is already in the table and returns the value
void* HashSearch(HT* ht, char* key){
    assert(key != NULL);
    KVpair* LLNode;
    int size = ht->size;
    int location = (int)Hash(key) % size;

    if(ht->table[location] == NULL){
        return NULL;
    }else{
        LLNode = ht->table[location];
        //compares the LL key to the key being passed in
        while(strcmp(LLNode->key,key)!=0){
            LLNode = LLNode->next;
            if (LLNode == NULL){
                return NULL;
            }
        }
        return LLNode->val;        // returns the value of the table location
    }
    return NULL;
}



//the apply function that will apply the print method and print off the key and value
void HashApply(HT* table,KVpair** list,int printnum, void(*func)(KVpair*, int)){
    int x = 0;
    for (int i = 0;i<printnum;i++){
        KVpair* current=list[i];
            func(current,x++);
    }
}

KVpair** Array(HT* table){
    int x = 0;
    KVpair** tmp = malloc(sizeof(KVpair*)*(table->count)); // allocates memroy for temp node
    for (int k = 0;k<table->count;k++){
        tmp[k] = NULL;                      // sets the entries in the temp node to null
    }
    for (int i = 0;i<table->size;i++){
        KVpair* current=table->table[i];
        // makes the array with the contents of the hashtable
        while (current != NULL){
            tmp[x] = current;
            x++;
            current = current->next;
        }
    }
    return tmp;
    
}

//frees the hashtable
void HashFree(HT* ht){
    KVpair* Ncurrent;
    KVpair* Ntemp;
    int i = 0;
    while(i < ht->size){
        if((ht->table[i]) == NULL){
            i++;
            continue;
        }
        Ncurrent = ht->table[i];
        do{
            Ntemp = Ncurrent->next;
            free(Ncurrent);
            Ncurrent = Ntemp;
        }while((Ncurrent) != NULL);
        i++;
    }
    free(ht->table);
    free(ht);
}

