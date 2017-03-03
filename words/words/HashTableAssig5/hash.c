#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"


float HashLoadfactor(HashTable* table);
static void HashRehash(HashTable* table);


//This determines how full the hashtable
float HashLoadfactor(HashTable* table){
    return (float)((table->Entries)/(table->Size));
}

//this Initializes the hash table
 HashTable* HashInit(int buckets){
    HashTable* table;
    if((table = malloc(sizeof(HashTable)))==NULL){  //makes room for the table
        return NULL;
    }
    // allocates memory for the LL.
    if((table->LL = malloc(buckets*sizeof(Node*)))== NULL){
        return NULL;
    }
    for(int i = 0; i<buckets; i++){
      table->LL[i]=NULL; // fills the spots with Null with how many buckets there are
    }
    table->Size = buckets;  // the size of the table is the amount of buckets
    table->Entries = 0;
    return table;
}



int HashInsert(HashTable* table,char* key,void* val){
    if((HashLoadfactor(table)) >= 0.7){                     //checks to see how full the table is
        printf ("Table is getting full. Needs to be rehashed\n");
        HashRehash(table);                                  // rehashes if needed to
    }
    int location = Hash(key) % table->Size;
    Node* LLNode = table->LL[location];
    //linked list is empty, put new entry in the first spot.
    if (LLNode==NULL){
        //makes room and sets everything to the new node
        Node* newN = (Node*)malloc(sizeof(Node));
        newN->key =key;
        newN->val = val;
        newN->next = LLNode;
        table->LL[location] = newN;
        table->Entries++;
        return 0;
    }
    else{
        //compares the node key with the new key that being passed through
        while (strcmp(LLNode->key,key)!= 0){
            LLNode = LLNode->next;
            if (LLNode==NULL){
                //if the node is empty it sets the key to that node
                Node* newN = (Node*)malloc(sizeof(Node));
                newN->key =key;
                newN->val = val;
                newN->next = table->LL[location];   //the next node would be the next bucket in the LL
                table->LL[location] = newN;         // the LL location would be the new node
                table->Entries++;
                return 0;
            }
        }
        LLNode->val = val;      // the current node value is then updated
    }
    return 0;
    
}

//hash function to determine where each key will go
int Hash(char* key){
  
    int hashvalue = 0;
    char *p = key;
    for (int i = 0;i<strlen(key);i++){
        hashvalue = (33 * hashvalue)+p[i];
        
    }
    if (hashvalue < 0){return -hashvalue;}
    return hashvalue;
    
}

//this searches the table checking if the key is already in the table and returns the value
void* HashSearch(HashTable* ht, char* key){
    Node* LL;
    int size = ht->Size;
    int location = (int)Hash(key) % size;
    // if the LL is Null returns Null
    if(ht->LL[location] == NULL){
        return NULL;
    }else{
        LL = ht->LL[location];
        //compares the LL key to the key being passed in
        while(strcmp(LL->key,key)!=0){
	      LL = LL->next;
              if (LL == NULL){
		return NULL;
	      }
    }
	return LL->val;        // returns the value of the table location
    }
    return NULL;
}

//this takes all the key and values from the old table doubles the size
// and inserts everything back to the new hashtable
static void HashRehash(HashTable* table){
     HashTable* old = table;
     printf("new size will be: %i\n",(int)(table->Size)*3);
     HashTable* newtable = HashInit((table->Size)*3);  //double the table size.
     Node* Current = NULL;
     int i = 0;
     while (i < (table->Size)){
      Current = old->LL[i];
        
      if(Current == NULL){
          i++;
      }
      else{
          do{
              HashInsert(newtable, Current->key, Current->val); // inserts everything back in the new table
          }while((Current = Current->next) != NULL);
          i++;
      }
     }
     free(Current);
     free(old->LL);
     *old = *newtable;
     free(newtable);
}


//the apply function that will apply the print method and print off the key and value
void HashApply(HashTable* table, void(*func)(Node*, int)){
   int x = 0;
    for (int i = 0;i<table->Size;i++){
        Node* current=table->LL[i];
        while (current != NULL){
            func(current,x++);
            current = current->next;
        }
    }
}

// this is similar to hashapply but will make an array of the words instead
Node** Array(HashTable* table){
    int x = 0;
    Node** tmp = malloc(sizeof(Node*)*(table->Entries)); // allocates memroy for temp node
    for (int k = 0;k<table->Entries;k++){
        tmp[k] = NULL;                      // sets the entries in the temp node to null
    }
    for (int i = 0;i<table->Size;i++){
        Node* current=table->LL[i];
        // makes the array with the contents of the hashtable
        while (current != NULL){
            tmp[x] = current;
            x++;
            current = current->next;
        }
    }	
    return tmp;
    
}

//this frees the heap allocated memory used by the table
void HashFree(HashTable* ht){
    Node* Ncurrent;
    Node* Ntemp;
    int i = 0;
    while(i < ht->Size){
        if((ht->LL[i]) == NULL){
            i++;
            continue;
        }
        Ncurrent = ht->LL[i];
        do{
            Ntemp = Ncurrent->next;
            free(Ncurrent);
            Ncurrent = Ntemp;
        }while((Ncurrent) != NULL);
        i++;
    }
    free(ht->LL);
    free(ht);            
}







