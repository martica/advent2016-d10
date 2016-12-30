//
// Created by Tyler Bindon on 2016-12-30.
//

#include <string.h>
#include <stdio.h>

#include "wrappedarray.h"

Object *array_get_item(Array *array, unsigned int index) {
  if (index > array->size) {
    return NULL;
  }
  return array->items[index];
}

void array_set_item(Array *array, unsigned int index, Object *object) {
  if (index > array->size) {
    unsigned int old_size = array->size;
    array->size = index * 2;
    array->items = realloc(array->items, array->size * sizeof(Object *));
    memset(array->items + old_size, 0, array->size - old_size);
  }
  RETAIN(object);
  Object *old_object = array->items[index];
  if (old_object != NULL) {
    RELEASE(old_object);
  }
  array->items[index] = object;
}

void Array_init(Object *object) {
  Array *array = (Array *)object;

  *array = (Array) {
      .size = 10,
      .items = calloc(10, sizeof(Object *)),
      .get_item = Block_copy(^(unsigned int index) {return (void *) array_get_item(array, index);}),
      .set_item = Block_copy(^(unsigned int index, void *object) {array_set_item(array, index, object);}),
      .header.destroy = Block_copy(^() {
        printf("freeing array with size: %u\n", array->size);
        for (int i=0; i<array->size; i++) {
          if (array->items[i] != NULL) {
            RELEASE(array->items[i]);
          }
        }
        free(array->items);
        Block_release(array->get_item);
        Block_release(array->set_item);
    })};
}
Array *Array_create() {
  return CREATE(Array, (^(Object *o) { Array_init(o);}));
}

