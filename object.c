
#include <printf.h>
#include "object.h"

void *constructor(size_t size, char *type_name, init_type init) {
  Object *object = calloc(1, size);

  object->methods = calloc(100, sizeof(void *));
  object->method_count = 0;

  init(object);

  object->methods = realloc(object->methods, sizeof(void *) * object->method_count);
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
    for (int i=0; i<object->method_count; i++) {
      Block_release(object->methods[i]);
    }
    free(object->methods);
    free(object);
  }
}

const void *define_method(Object *object, const void *aBlock) {
  const void *retainedBlock = Block_copy(aBlock);
  object->methods[object->method_count] = retainedBlock;
  object->method_count++;
  return retainedBlock;
}

void destructor(Object *object, const void *block) {
  object->destroy = Block_copy(block);
}