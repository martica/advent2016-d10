//
// Created by Tyler Bindon on 2016-12-29.
//

#ifndef ADVENT10_DESTRUCTOR_H
#define ADVENT10_DESTRUCTOR_H

struct destructable {
  void (^destroy)();
};

void destructor(struct destructable *to_destroy);

#define DESTROY(x) destructor((struct destructable *) x);

#endif //ADVENT10_DESTRUCTOR_H
