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
  void * (^get_item)(unsigned int index);
  void (^set_item)(unsigned int index, void *item);
} Array;

Array *Array_create();

#endif //ADVENT10_WRAPPEDARRAY_H
