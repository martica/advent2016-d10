#include <assert.h>
#include <stdlib.h>
#include <Block.h>
#include <printf.h>

#include "linkedlist.h"
#include "destructor.h"

void ll_add(struct ll_t *list, void *object) {
  struct ll_entry *node;
  node = calloc(sizeof(struct ll_entry), 1);
  node->data = object;
  if (list->head == NULL) {
    assert(list->tail == NULL);
    list->head = node;
    list->tail = node;
  } else {
    assert(list->tail != NULL);
    list->tail->next = node;
    list->tail = node;
  }
}

void *ll_pop(struct ll_t *list) {
  if (list->head == NULL) {
    return NULL;
  }

  struct ll_entry *head = list->head;
  list->head = list->head->next;

  if (list->head == NULL) {
    list->tail = NULL;
  }

  void *data = head->data;
  free(head);

  return data;
}

int ll_is_empty(struct ll_t *list) { return list->head == NULL; }

struct ll_t *ll_create() {
  struct ll_t *list = calloc(sizeof(struct ll_t), 1);

  list->add = Block_copy(^(void *object) {ll_add(list, object);});
  list->pop = Block_copy(^(void *object) {return ll_pop(list);});
  list->is_empty = Block_copy(^() {return ll_is_empty(list);});
  list->destroy = Block_copy(^ {
    while(!list->is_empty()) {
      DESTROY(list->pop());
    }
    Block_release(list->add);
    Block_release(list->pop);
    Block_release(list->is_empty);
  });

  return list;
}

