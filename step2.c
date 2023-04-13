#include "functions.c"
#include <stdlib.h>

#define BLOCKSIZE 2




int main() {
	int counter = 0;
    	struct list myList;
      	initialiseList(&myList, &counter);
        printList(&myList, &counter);
        allocateBlock(&myList, &counter, BLOCKSIZE);
        printList(&myList, &counter);
        deAllocateBlock(&myList, &counter, BLOCKSIZE);
        printList(&myList, &counter);
        freeList(&myList, &counter);
        printList(&myList, &counter);
}
