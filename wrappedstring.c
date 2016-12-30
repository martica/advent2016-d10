//
// Created by Tyler Bindon on 2016-12-30.
//

#include <string.h>
#include "wrappedstring.h"

void String_init(Object *object, char *value) {
  String *string = (String *)object;

  *string = (String) {
      .value = strdup(value),
      .get_value = Block_copy(^{return string->value;}),
      .header.destroy = Block_copy(^{
        free(string->value);
      })
  };
}

String *String_create(char *string) {
  return CREATE(String, (^(Object *o) { String_init(o, string);}));
}
