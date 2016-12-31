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

  array->get_item = METHOD(
      array,
      ^(unsigned int index) {
        return (void *) array_get_item(array, index);
      });
  array->set_item = METHOD(
      array,
      ^(unsigned int index, void *object) {
        array_set_item(array, index, object);
      });
  DESTRUCTOR(array, ^{
        for (int i=0; i<array->size; i++) {
          if (array->items[i] != NULL) {
            RELEASE(array->items[i]);
          }
        }
        free(array->items);
    });
}
Array *Array_create() {
  Array *array = CREATE(Array, Array_init);
  array->size = 10;
  array->items = calloc(10, sizeof(Object *));
  return array;
}

