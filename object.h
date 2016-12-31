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
  const void **methods;
  unsigned int method_count;
} Object;

typedef void (*init_type)(Object *o);

void *constructor(size_t size, char *type_name, init_type init);
void retain(Object *object);
void release(Object *object);
const void *define_method(Object *object, const void *aBlock);
void destructor(Object *, const void *block);

#define CREATE(x, y) constructor(sizeof(x), #x, (init_type)y)
#define METHOD(obj, ...) ((__typeof(__VA_ARGS__))define_method((Object *) obj, (const void *)(__VA_ARGS__)))
#define RELEASE(x) release((Object *)x)
#define RETAIN(x) retain((Object *)x)
#define DESTRUCTOR(obj, block) destructor((Object *)obj, block)

#endif  // ADVENT10_DESTRUCTOR_H
