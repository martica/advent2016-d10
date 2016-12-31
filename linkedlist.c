#include <Block.h>
#include <assert.h>
#include <printf.h>
#include <stdlib.h>

#include "object.h"
#include "linkedlist.h"

void ll_add(LinkedList *list, void *object) {
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

void *ll_pop(LinkedList *list) {
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

void LinkedList_init(Object *object) {
  LinkedList *list = (LinkedList *) object;

  list->add = METHOD(list, ^(void *obj) {ll_add(list, obj);});
  list->pop = METHOD(list, ^ {return ll_pop(list);});
  list->is_empty = METHOD(list, ^int {return list->head == NULL;});
  DESTRUCTOR(list, ^{ while (!list->is_empty()) { RELEASE(list->pop()); } });
}

LinkedList *ll_create() {
  return CREATE(LinkedList, LinkedList_init);
}
