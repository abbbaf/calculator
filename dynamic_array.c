#include "./dynamic_array.h"

#define FREED_LIST -1

List new_list() {
  List list;
  list.array = malloc(MIN_CAPACITY*sizeof(void *));
  list.size = 0;
  list.capacity = MIN_CAPACITY;
  return list;
}

void assert_list_not_free(List * list) {
  if (list->capacity == -1) {
    printf("List has been freed");
    exit(1);
  }
}

void update_array(List *list,int new_capacity) {
  list->array = realloc(list->array,new_capacity*sizeof(list->array[0]));
  list->capacity = new_capacity;;
}

void push(List *list, void * element) {
  assert_list_not_free(list);
  int capacity = list->capacity;
  if (list->size >= capacity) update_array(list,capacity*2);
  list->array[list->size++] = element;
}

void * pop(List *list) {
  assert_list_not_free(list);
  if (!list->size) return NULL;
  int capacity = list->capacity;
  if (list->size*4 <= capacity && capacity >= 2*MIN_CAPACITY) 
    update_array(list,capacity/2);
  return list->array[--list->size];
}

void * get_last_element(List *list) {
  assert_list_not_free(list);
  if (!list->size) return NULL; 
  return list->array[list->size-1];
}

void reverse(List * list) {
  assert_list_not_free(list);
  void * temp;
  for (int i = 0; i < list->size/2; i++) {
    temp = list->array[i];
    list->array[i] = list->array[list->size - i - 1];
    list->array[list->size - i - 1] = temp;
  }
}


void free_list(List *list) {
  assert_list_not_free(list);
  for (int i = 0; i < list->size; i++)
    free(list->array[i]);
  free(list->array);
  list->capacity = -1;
}

