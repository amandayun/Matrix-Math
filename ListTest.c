//Amanda Yun, akyun, 1903241, pa4
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>

int main(int argc, char **argv) {
	List L = newList();
	int num = 9;
	int num2 = 19;
	int num3 = 919;
	int num4 = 1919;

	append(L, &num);
	moveFront(L);
	insertBefore(L, &num2);
	moveBack(L);
	insertAfter(L, &num3);
	
	printf("testing isEmpty: %d\n", isEmpty(L));
	printf("testing length: %d\n", length(L));
	printf("testing index: %d\n", index(L));
	printf("getting front: %p\n", front(L));
	printf("getting back: %p\n", back(L));
	moveNext(L);
	printf("getting at cursor: %p\n", get(L));
	prepend(L, &num4);
	delete(L);
	printf("testing length after delete: %d\n", length(L));
	deleteBack(L);
	printf("testing length after deleteBack: %d\n", length(L));
	deleteFront(L);
	printf("testing length after deleteFront: %d\n", length(L));
	
	
	freeList(&L);
	
	

	return 0;
}