#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

#define SIZE 40

struct table{
    int data;
    int key;
};

struct table* globalArray[SIZE];
struct table* dummyItem;

int get_HashKey(int key);
void print_HashTable(void);
void insert_HashTable(int key, int data);
void delete_HashItem(struct table* item);
struct table* search_HashKey(int key);
struct table* search_HashData(int data);
