#include "functions.c"
#include <stdlib.h>


int main() {
  int counter = 0;
  struct list myList;
  initialiseList(&myList, &counter);
  printList(&myList, &counter);
  freeList(&myList, &counter);
  printList(&myList, &counter);
}

