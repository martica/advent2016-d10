#include <Block.h>
#include <stdlib.h>
#include <string.h>

#include "object.h"

void *constructor(size_t size, init_type init) {
  Object *object = calloc(1, size);

  init(object);

  return object;
}

void destructor(Object *to_destroy) {
  if (to_destroy->destroy != NULL) {
    to_destroy->destroy();
    Block_release(to_destroy->destroy);
  }
  free(to_destroy);
}
