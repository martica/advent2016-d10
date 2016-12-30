//
// Created by Tyler Bindon on 2016-12-29.
//

#ifndef ADVENT10_DESTRUCTOR_H
#define ADVENT10_DESTRUCTOR_H

typedef struct object {
  void (^destroy)();
} Object;

typedef void (^init_type)(Object *o);

void destructor(Object *to_destroy);
void *constructor(size_t size, init_type init);

#define DESTROY(x) destructor((Object *)x);
#define CREATE(x, y) constructor(sizeof(x), (init_type)y);

#endif  // ADVENT10_DESTRUCTOR_H
