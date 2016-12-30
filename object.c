
#include "object.h"

void *constructor(size_t size, init_type init) {
  Object *object = calloc(1, size);

  object->retain_count = 1;
  init(object);

  return object;
}

void retain(Object *object) {
  object->retain_count++;
}

void release(Object *object) {
  object->retain_count--;
  if (object->retain_count == 0) {
    if (object->destroy != NULL) {
      object->destroy();
      Block_release(object->destroy);
    }
    free(object);
  }
}
