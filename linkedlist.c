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

void LinkedList_init(Object *alloc) {
  LinkedList *linkedList = (LinkedList *) alloc;

  *linkedList = (LinkedList) {
      .add = Block_copy(^(void *object) {ll_add(linkedList, object);}),
      .pop = Block_copy(^(void *object) {return ll_pop(linkedList);}),
      .is_empty = Block_copy(^int() {return linkedList->head == NULL;}),
      .header.destroy = Block_copy(^{
        while (!linkedList->is_empty()) {
          RELEASE(linkedList->pop());
        }
        Block_release(linkedList->add);
        Block_release(linkedList->pop);
        Block_release(linkedList->is_empty);
      })
  };
}

LinkedList *ll_create() {
  return CREATE(LinkedList, (^(Object *o) { LinkedList_init(o);}));
}
