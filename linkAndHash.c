//#include "hashTable.h"
//#include "linkedList.h"
#include "string.h"
#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"

#define SIZE 256 //ASCII SIZE

struct _node{
    char *key;
    uint8_t data;
    struct _node* nextNode;
};

struct _mainTable{
    uint8_t key;
    struct _node* root;    
};

struct _mainTable* mainTable[SIZE];

void yapSovunuCanim(void){
    struct _node *ptr;
    uint8_t counter_hashCell;

    for(counter_hashCell = 0; counter_hashCell<SIZE; counter_hashCell++){
        if(mainTable[counter_hashCell] != NULL){
            printf(" (%d,%s) ",mainTable[counter_hashCell]->root->key[0],mainTable[counter_hashCell]->root->data);

            ptr = mainTable[counter_hashCell]->root;
            while(ptr != NULL){
                printf("/n");
                printf(" (%d,%d) ",ptr->key,ptr->data);                
                ptr = ptr->nextNode;
            }
        }else{
            //printf(" (~ , ~) ");
        }
    }

}

int get_HashKey(int key){
    
    key = abs(key);
    while(key>SIZE){
        key %= SIZE;
    }
    return key;
}

void delete_linklistElement(struct _node* _root,char key[]){
    struct _node* tempList;
    char ptr;

    ptr = strcmp(_root->key,key);
    if(ptr == 0){
        tempList = _root->nextNode;
        _root->data = _root->nextNode->data;
        _root->key  = _root->nextNode->key;
        _root->nextNode = _root->nextNode->nextNode;
        free(tempList);
        return;
    }
    ptr = strcmp(_root->nextNode->key,key);
    while(key!=0){
        _root = _root->nextNode;
        ptr = strcmp(_root->nextNode->key,key);
    }
    tempList = _root->nextNode;
    _root->nextNode = _root->nextNode->nextNode;
    free(tempList);
}

void delete_Item(char key[]){
    uint16_t item_HashKey;

    item_HashKey = get_HashKey((int)key[0]);
    delete_linklistElement(mainTable[item_HashKey]->root,key);
}

struct _node* add_linklistElement(struct _node* _root,char key[],uint8_t _data){
    char ptr;

    if(_root == NULL){
        _root = (struct _node*)malloc(sizeof(struct _node*));
        _root->data = _data;
        _root->key  = key;
        _root->nextNode = NULL;

        return _root; 
    }

    ptr = strcmp(_root->key,key);
    if(ptr > 0){
        struct _node* tempList = (struct _node*)malloc(sizeof(struct _node*));
        tempList->data = _data;
        tempList->key = key;
        tempList->nextNode = _root;
        return tempList;
    }

    struct _node* iter = _root;
    ptr = strcmp(iter->key,key);
    while(iter->nextNode != NULL && ptr<0){
        iter = iter->nextNode;
    }

    struct _node* tempLinkList = (struct _node*)malloc(sizeof(struct _node*));
    tempLinkList->nextNode = iter->nextNode;
    iter->nextNode = tempLinkList;
    tempLinkList->data = _data;
    tempLinkList->key  = key;
    return _root;
}

void add_Item(char key[],uint8_t _data){
    uint16_t item_HashKey;

    item_HashKey = get_HashKey((int)key[0]);

    if(mainTable[item_HashKey] != NULL){
        mainTable[item_HashKey]->root = add_linklistElement(mainTable[item_HashKey]->root,key,_data);
    }else{
        mainTable[item_HashKey] = (struct _mainTable*)malloc(sizeof(struct _mainTable*));
        mainTable[item_HashKey]->key = item_HashKey;

        mainTable[item_HashKey]->root = (struct _node*)malloc(sizeof(struct _node*));
        mainTable[item_HashKey]->root->data = _data;
        mainTable[item_HashKey]->root->key  = key;
        mainTable[item_HashKey]->root->nextNode = NULL;
    }
}

void main(void){
    add_Item("141",225);
    add_Item("256",44);
    add_Item("Ahmet",56);
    add_Item("68" ,50);
    add_Item("350",190);
    add_Item("125",100);
    add_Item("156",99);

    delete_Item("125");

    yapSovunuCanim();
}