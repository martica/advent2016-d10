//
// Created by Tyler Bindon on 2016-12-29.
//

#ifndef ADVENT10_DESTRUCTOR_H
#define ADVENT10_DESTRUCTOR_H
#include <Block.h>
#include <stdlib.h>

typedef struct object {
  void (^destroy)();
  int retain_count;
  char *type_name;
} Object;

typedef void (^init_type)(Object *o);

void *constructor(size_t size, char *type_name, init_type init);
void retain(Object *object);
void release(Object *object);

#define RELEASE(x) release((Object *)x);
#define RETAIN(x) retain((Object *)x);
#define CREATE(x, y) constructor(sizeof(x), #x, (init_type)y);

#endif  // ADVENT10_DESTRUCTOR_H
