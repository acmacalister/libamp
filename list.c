////////////////////////////////////////////////////////////////////////////////
//
//  list.c
//
//  Created by Austin Cherry on 9/17/15.
//  Copyright (c) 2015 Vluxe. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "list.h"
#include <stdbool.h>

////////////////////////////////////////////////////////////////////////////////
List *newList() {
  List *list = (List*)malloc(sizeof(List));
  list->count = 0;
  list->head = NULL;
  list->tail = NULL;
  return list; 
}
////////////////////////////////////////////////////////////////////////////////
Node *llfront(List *l) {
  if(l->count == 0) {
    return NULL;
  }
  return l->head;
}
////////////////////////////////////////////////////////////////////////////////
Node *llback(List *l) {
  if(l->count == 0) {
    return NULL;
  }
  return l->tail;
}
////////////////////////////////////////////////////////////////////////////////
void *llremove(List *l, Node *n) {
  if(l->count == 0 || !n) {
    return NULL;
  }

  if(n == l->head && n == l->tail) {
    l->head = NULL;
    l->tail = NULL;
  } else if(n == l->head) {
    l->head = n->next;
    l->head->prev = NULL;
  } else if (n == l->tail) {
    l->tail = n->prev;
    l->tail->next = NULL;
  } else {
    n->prev->next = n->next;
    n->next->prev = n->prev;
    n->next = NULL;
    n->prev = NULL;
  }

  l->count--;
  free(n);
  return n->value;
}
////////////////////////////////////////////////////////////////////////////////
Node *insert(List *l, void *value, Node *at, bool isTail) {
  Node *newNode = (Node*)malloc(sizeof(Node));
  newNode->prev = NULL;
  newNode->next = NULL;
  newNode->value = value;

  if(!l->head) {
    l->head = newNode;
    l->tail = newNode;
  } else if(l->head == at && !isTail) {
    newNode->next = l->head;
    l->head->prev = newNode;
    l->head = newNode;
  } else if(l->tail == at && isTail) {
    l->tail->next = newNode;
    newNode->prev = l->tail;
    l->tail = newNode;
  } else {
    Node *n = at->next;
    at->next = newNode;
    newNode->prev = at;
    newNode->next = n;
    n->prev = newNode;
  }

  l->count++;
  return newNode;
}
////////////////////////////////////////////////////////////////////////////////
Node *llpushFront(List *l, void *value) {
  return insert(l, value, l->head, false);
}
////////////////////////////////////////////////////////////////////////////////
Node *llpushBack(List *l, void *value) {
  return insert(l, value, l->tail, true);
}
////////////////////////////////////////////////////////////////////////////////
void *llpopFront(List *l) {
  return llremove(l, l->head);
}
////////////////////////////////////////////////////////////////////////////////
void *llpopBack(List *l) {
  return llremove(l, l->tail);
}
////////////////////////////////////////////////////////////////////////////////
Node *llinsertAfter(List *l, void *value, Node *mark) {
  return insert(l, value, mark->next, false);
}
////////////////////////////////////////////////////////////////////////////////
Node *llinsertBefore(List *l, void *value, Node *mark) {
  return insert(l, value, mark->prev, false);
}
////////////////////////////////////////////////////////////////////////////////
void llclear(List *l) {
  void *value = llpopBack(l);
  while(value) {
    free(value);
    value = llpopBack(l);
  }
}
////////////////////////////////////////////////////////////////////////////////
void freeList(List *l) {
  llclear(l);
  free(l);
}
////////////////////////////////////////////////////////////////////////////////