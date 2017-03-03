#ifndef HASHTABLE_H
#define HASHTABLE_H

// the node that goes into the hashtable
typedef struct Node{
    struct Node *next;
    char* key;
    void* val;
}Node;

// the hashtable that will contain all the entries
typedef struct hashtable{
    int Size;               // size of the hashtable
    int Entries;            // the entries in the table
    struct Node **LL;      
}HashTable;

// this determines where in the table the key will be placed
int Hash(char* key);

// initializes the table so keys can be inserted
HashTable* HashInit(int buckets);

//searches for the key in the table and returns the value
void* HashSearch(HashTable* ht, char *key);

//inserts the key and value in to the table and calls rehash if needed
int HashInsert(HashTable* ht, char* key, void* val);

//this is the function to print out the hashtable
void HashApply(HashTable* ht, void(*func)(struct Node* , int));

//frees the heap allocated memory
void HashFree(HashTable* ht);

// makes array of the contents of the table
Node** Array(HashTable* table);

#endif
