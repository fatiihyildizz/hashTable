#include "hashTable.h"

int get_HashKey(int key){
    return key%SIZE;
}

void print_HashTable(void){
    int counter = 0;

    for(counter = 0; counter<SIZE; counter++){
        if(globalArray[counter]!= NULL){
            printf(" (%d, %d) ",globalArray[counter]->key,globalArray[counter]->data);
        }else{
            printf(" (--, --) ");
        }
    }    
    printf("\n");
}

void insert_HashTable(int key, int data){
    struct table* item = (struct table*)malloc(sizeof(struct table*));
    item->data = data;
    item->key = key;
    
    int hashID = get_HashKey(key);
    while(globalArray[hashID]!=NULL && globalArray[hashID]->data != -1){
        hashID++;

        hashID %= SIZE;
    }

    globalArray[hashID] = item;
}

void delete_HashItem(struct table* item){
    int key = item->key;

    int hashID = get_HashKey(key);

    while(globalArray[hashID] != NULL){
        if(globalArray[hashID]->data == item->data){
            globalArray[hashID] = dummyItem;
        }

        hashID++;
        hashID %= SIZE;
    }
}

struct table* search_HashKey(int key){
    int counter;

    for(counter = 0; counter<SIZE; counter++){
        if(globalArray[counter]->key == key){
            return globalArray[counter];
        }
    }

    return NULL;
}

struct table* search_HashData(int data){
    int counter;

    for(counter = 0; counter<SIZE; counter++){
        if(globalArray[counter]!=NULL){
            if(globalArray[counter]->data == data){
                return globalArray[counter];
            }
        }
    }
    return NULL;
}

void main(void){
    dummyItem = (struct table*)malloc(sizeof(struct table*));
    dummyItem->data = -1;
    dummyItem->key  = -1;
}