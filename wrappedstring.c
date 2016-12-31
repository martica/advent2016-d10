//
// Created by Tyler Bindon on 2016-12-30.
//

#include <string.h>
#include "wrappedstring.h"

void String_init(Object *object, char *value) {
  String *string = (String *)object;

  string->value = strdup(value);
  string->get_value = METHOD(string, ^{return string->value;});
  DESTRUCTOR(string, ^{free(string->value);});
}

String *String_create(char *string) {
  return CREATE(String, (^(Object *o) { String_init(o, string);}));
}
