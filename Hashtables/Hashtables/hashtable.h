//
//  hashtable.h
//  Hashtables
//
//  Created by David Ciupei on 1/28/16.
//  Copyright © 2016 David Ciupei. All rights reserved.
//


#ifndef hashtable_h
#define hashtable_h

#include <stdio.h>

typedef struct KVpair{
    struct KVpair *next;
    char* key;
    void* val;
}KVpair;

typedef struct _ht{
    int count;
    int size;
    struct KVpair **table;
}HT;

void* HashSearch(HT* ht, char* key);
HT* HashInit(int buckets);
int HashInsert(HT* ht, char* key, void* val);
void HashApply(HT* ht,KVpair** list,int printnum, void(*func)(struct KVpair* , int));
KVpair** Array(HT* table);
void HashFree(HT* ht);
int Hash(char* key);
static void HashRehash(HT* table);
float HashLoadfactor(HT* table);

#endif /* hashtable_h */
