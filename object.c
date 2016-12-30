
#include <printf.h>
#include "object.h"

void *constructor(size_t size, char *name, init_type init) {
  Object *object = calloc(1, size);

  init(object);
  object->retain_count = 1;
  object->name = name;

  return object;
}

void retain(Object *object) {
  object->retain_count++;
}

void release(Object *object) {
  object->retain_count--;
  printf("releasing %s: %d\n", object->name, object->retain_count);
  if (object->retain_count == 0) {
    if (object->destroy != NULL) {
      object->destroy();
      Block_release(object->destroy);
    }
    free(object);
  }
}
