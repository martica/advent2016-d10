
#include <printf.h>
#include "object.h"

void *constructor(size_t size, char *type_name, init_type init) {
  Object *object = calloc(1, size);

  init(object);
  object->retain_count = 1;
  object->type_name = type_name;

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
