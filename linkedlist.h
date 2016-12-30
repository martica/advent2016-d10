//
// Created by Tyler Bindon on 2016-12-30.
//

#ifndef ADVENT10_LINKEDLIST_H
#define ADVENT10_LINKEDLIST_H

#include "object.h"

struct ll_entry {
  struct ll_entry *next;
  void *data;
};

typedef struct ll_t {
  Object header;
  void (^add)(void *object);
  void * (^pop)();
  int (^is_empty)();
  struct ll_entry *head;
  struct ll_entry *tail;
} LinkedList;

LinkedList *ll_create();

#endif //ADVENT10_LINKEDLIST_H
