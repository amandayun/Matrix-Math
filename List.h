//Amanda Yun, akyun, 1903241, pa4
#include <stdio.h>
#include <stdbool.h>


//typedef void* ListElement;
typedef struct ListObj* List;


//constructor and destructor
List newList(void);

void freeList(List* pL);

int isEmpty(List L);

//void printList(FILE* out, List L);

//bool equals(List A, List B);

int length(List L);

int index(List L);

void* front(List L);

void* back(List L);

void* get(List L);

void append(List L, void* x);

void prepend(List L, void* x);

void deleteBack(List L);
void deleteFront(List L);


void clear(List L);

void set(List L, void* x);

void moveBack(List L);

void moveFront(List L);
void movePrev(List L);
void moveNext(List L);
void insertBefore(List L, void* x);
void insertAfter(List L, void* x);
void delete(List L);

//List copyList(List L);