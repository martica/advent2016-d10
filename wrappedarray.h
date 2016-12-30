//
// Created by Tyler Bindon on 2016-12-30.
//

#ifndef ADVENT10_WRAPPEDARRAY_H
#define ADVENT10_WRAPPEDARRAY_H

#include "object.h"

typedef struct Array {
  Object header;
  Object **items;
  unsigned int size;
  Object * (^get_item)(unsigned int index);
  void (^set_item)(unsigned int index, Object *item);
} Array;

Array *Array_create(unsigned int size);

#endif //ADVENT10_WRAPPEDARRAY_H
