#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MIN_CAPACITY 10

typedef struct List_type {
  size_t size;
  size_t capacity;
  void ** array;
} List; 

List new_list();

void create_new_array(List *list, int new_capacity);

void push(List *list, void * element);

void * pop(List *list);

void reverse(List *list);

void * get_last_element(List *list);

void free_list(List *list);
