#include "list.h"
#include <stdio.h>

void listTest() {
  List *l = newList();

  printf("Testing a stack...\n");

  // We got a stack.
  llpushFront(l, "Austin");
  llpushFront(l, "Dalton");
  llpushFront(l, "Dave");
  llpushFront(l, "Matt");

  char *name = (char *)llpopFront(l);
  while(name) {
    printf("%s\n", name);
    name = (char *)llpopFront(l);
  }

  printf("Testing a queue...\n");
  llclear(l);

  //Queue time!
  llpushBack(l, "Austin");
  llpushBack(l, "Dalton");
  llpushBack(l, "Dave");
  llpushBack(l, "Matt");

  name = (char *)llpopFront(l);
  while(name) {
    printf("%s\n", name);
    name = (char *)llpopFront(l);
  }

  printf("Testing list cleanup and iterator.\n");

  llpushBack(l, strdup("Austin"));
  llpushBack(l, strdup("Dalton"));
  llpushBack(l, strdup("Dave"));
  llpushBack(l, strdup("Matt"));

  LIST_ITERATE(l, cur) {
    printf("iterating list %s\n", (char *)cur->value);
  }

  printf("Freeing List\n");
  freeList(l);
}