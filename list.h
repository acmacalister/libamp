////////////////////////////////////////////////////////////////////////////////
//
//  list.h
//
//  Created by Austin Cherry on 9/17/15.
//  Copyright (c) 2015 Vluxe. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __AMP__List__
#define __AMP__List__

#include <stdlib.h>

struct Node;

typedef struct Node {
  struct Node *next;
  struct Node *prev;
  void *value;
} Node;

typedef struct List {
  int count;
  Node *head;
  Node *tail;
} List;

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
List *newList();

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
Node *llfront(List *l);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
Node *llback(List *l);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
void *llremove(List *l, Node *n);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
Node *llpushFront(List *l, void *value);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
Node *llpushBack(List *l, void *value);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
void *llpopFront(List *l);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
void *llpopBack(List *l);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
Node *llinsertAfter(List *l, void *value,  Node *mark);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
Node *llinsertBefore(List *l, void *value, Node *mark);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
void llclear(List *l);

/**
 The websocket connected to its host.
 @param socket is the current socket object.
 */
void freeList(List *l);

#define LIST_ITERATE(list, current) \
    Node *current = NULL; \
    for(current = list->head; current != NULL; current = current->next)

#endif /* defined(__AMP__List__) */