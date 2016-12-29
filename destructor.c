#include <Block.h>
#include <stdlib.h>

#include "destructor.h"

void destructor(struct destructable *to_destroy) {
  to_destroy->destroy();
  Block_release(to_destroy->destroy);
  free(to_destroy);
}
