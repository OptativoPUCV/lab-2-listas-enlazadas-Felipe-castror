#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList()
{
    List* L  = (List*) malloc(sizeof(List));

    L -> head = NULL;
    L -> tail = NULL;
    L -> current = NULL;
    
    return L;
}

void * firstList(List * list) 
{
    if (!list ->head  )return NULL;
    list -> current = list->head;
    return list->current->data;
}

void * nextList(List * list)
{
    if (!list ->current || !list -> current -> next)return NULL;
    list->current = list->current-> next;
    return list->current->data;
}

void * lastList(List * list) 
{
    if(!list -> tail)return NULL;
    list -> current = list-> tail;
    return list -> current -> data;
}

void * prevList(List * list) 
{
    if(!list -> current || !list -> current -> prev)return NULL;
    list -> current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) 
{
    Node* newNode = createNode(data);
    if(list -> head == NULL)
    {
        list-> head = list -> tail = newNode;
    }

    else
    {
        newNode -> next = list -> head;
        newNode -> prev = NULL;

        list -> head -> prev = newNode;
        list-> head = newNode;

    }

}

void pushBack(List * list, void * data) 
{
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
    if (!list -> current)return;

    Node* newNode = createNode(data);
    newNode -> prev = list -> current;
    newNode -> next = list -> current -> next;

    if (list -> current -> next)list-> current -> next ->prev =newNode;
    else
    {
        list->tail = newNode;
    }
    
    list->current -> next = newNode;

}

void * popFront(List * list) 
{
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) 
{
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
    Node *aux = list->current;
    Node *izq = list-> current -> prev;
    Node *der = list-> current -> next;

    izq -> next = der;
    der -> prev = izq;
    free(list->current);
    list -> current = NULL;

    return aux -> data;
}

void cleanList(List * list) 
{
    while (list->head != NULL) 
    {
        popFront(list);
    }
}