//
// Created by Tyler Bindon on 2016-12-30.
//

#ifndef ADVENT10_STRING_H
#define ADVENT10_STRING_H

#include "object.h"

typedef struct String {
  Object header;
  char * (^get_value)();
  char *value;
} String;

String *String_create(char *value);

#endif //ADVENT10_STRING_H
