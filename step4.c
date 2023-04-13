#include "functions.c"
#include <stdlib.h>


#define BLOCKSIZE 2
#define maxInput 5*BLOCKSIZE

int main() {
	int counter = 0;
	struct list myList;
	initialiseList(&myList, &counter);
	printList(&myList, &counter);
	char sPush[maxInput];
	char sPull[maxInput];
	int lenPush = getInput(sPush);
	int lenPull = getInput(sPull);
	int i = 0;
	int j = 0;
	while ((i + j) < (lenPush + lenPull)) {
		if (i < lenPush) {
			pushInt(&myList, &counter, i);
			i++;
			printList(&myList, &counter);
		}
		if (j < lenPull) {
			pullInt(&myList, &counter, j);
			j++;
			printList(&myList, &counter);
		}
	}
	printList(&myList, &counter);
	clearList(&myList, &counter);
	printList(&myList, &counter);
}
