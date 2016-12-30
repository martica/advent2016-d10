//
// Created by Tyler Bindon on 2016-12-30.
//

#include "wrappedarray.h"

Object *array_get_item(Array *array, unsigned int index) {
  return array->items[index];
}

void array_set_item(Array *array, unsigned int index, Object *object) {
  RETAIN(object);
  Object *old_object = array->items[index];
  if (old_object != NULL) {
    RELEASE(old_object);
  }
  array->items[index] = object;
}

void Array_init(Object *object, unsigned int size) {
  Array *array = (Array *)object;

  *array = (Array) {
      .size = size,
      .items = calloc(size, sizeof(Object *)),
      .get_item = Block_copy(^(unsigned int index) {return array_get_item(array, index);}),
      .set_item = Block_copy(^(unsigned int index, Object *object) {array_set_item(array, index, object);}),
      .header.destroy = Block_copy(^() {
        for (int i=0; i<size; i++) {
          if (array->items[i] != NULL) {
            RELEASE(array->items[i]);
          }
        }
        Block_release(array->get_item);
        Block_release(array->set_item);
    })};
}
Array *Array_create(unsigned int size) {
  return CREATE(Array, (^(Object *o) { Array_init(o, size);}));
}

