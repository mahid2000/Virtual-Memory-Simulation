#include <stdio.h>
#include <stdlib.h>

#define BLOCKSIZE 2
#define maxInput 5*BLOCKSIZE

struct node {
        int i; // integer stored in node
        struct node *next; // right pointer
        struct node *prev; // left pointer
};

struct list {
        struct node *head; // list head pointer
        struct node *tail; // list tail pointer
        struct node *right; // top even pointer
        struct node *left; // top odd pointer
        int length; // number of nodes in free space
};


void printList(struct list *pList, int *counter) {
    struct node *cur  = pList->head;
    while (cur) {
        printf(" | %d | ", cur->i);
        cur = cur->next;
    }
    if (!(pList->head) || !(pList->tail) || *counter == 0)
        printf(" ||");
    printf("\ncounter = %d\n", *counter);
} 

void *allocator(int size, int *counter) {
	if (size != 0) {
		(*counter)++;
		return malloc(size);
	}
	return 0;
}

void deAllocator(void *p, int *counter){
	if (p != NULL) {
		free(p);
		(*counter)--;
	}	
}

void initialiseList(struct list *pList, int *counter) {
	(*pList).head = (struct node*)allocator(sizeof(struct node), (int*)counter);
	(*pList).tail = (struct node*)allocator(sizeof(struct node), (int*)counter);
	(*pList).head->next = (*pList).tail;
  	(*pList).tail->prev = (*pList).head;
  	(*pList).head->prev = NULL;
  	(*pList).tail->next = NULL;
  	(*pList).head->i = 0;
  	(*pList).tail->i = 0;
  	(*pList).left = (*pList).head;
  	(*pList).right = (*pList).tail;
  	(*pList).length = 0;
}

void freeList(struct list *pList, int *counter) {
	if (!(*pList).length && (*pList).head == (*pList).left && (*pList).tail == (*pList).right) {
		deAllocator((*pList).head, (int*)counter);
		deAllocator((*pList).tail, (int*)counter);
		if (!*counter) {
			(*pList).head = NULL;
    			(*pList).left = NULL;
    			(*pList).tail = NULL;
    			(*pList).right = NULL;
    			(*pList).length = -1;
		}		
	}
}

void allocateBlock(struct list *pList, int *counter, int nNodes) {
	//struct node space = (struct node*)allocator(sizeof(struct node), (int*)counter);
	for (int i = 0; i < (int)nNodes; i++) {
		struct node* space = (struct node*)allocator(sizeof(struct node), (int*)counter);
		space->i = -1;
		space->next = (*pList).left->next;
		(*pList).left->next = space;
		space->prev = (*pList).left;
		if (space->next != NULL) {
			(*space).next->prev = space;
		}
		(pList->length)++;
	}
}
	

void deAllocateBlock(struct list *pList, int *counter, int nNodes) {
	int n = (pList->length) - nNodes;
	while ((pList->length) > n) {
		struct node *temp = pList->left->next;
		pList->left->next->next->prev = pList->left;
		pList->left->next = temp->next;
		deAllocator(temp, counter);
		(pList->length)--;
	}
}


void pushInt(struct list *pList, int *counter, int i) {
	if((*pList).length == 0) {
		allocateBlock(pList, counter, BLOCKSIZE);
	}
	if(i%2==0) {
		struct node* even = allocator(sizeof(struct node), counter);
		even->i = i;
		even->next = (*pList).right->prev->next;
		(*pList).right->prev->next = even;
		even->prev = (*pList).right->prev;
		if (even->next != NULL) {
			(*even).next->prev = even;
		}
		pList->right = even;
		deAllocateBlock(pList,counter,1);
	} else {
		struct node* odd = allocator(sizeof(struct node), counter);
		odd->i = i;
		odd->next = (*pList).left->next;
		(*pList).left->next = odd;
		odd->prev = (*pList).left;
		if (odd->next != NULL) {
			(*odd).next->prev = odd;
		}
		pList->left = odd; 
		deAllocateBlock(pList,counter,1);
	}
}

void pullInt(struct list *pList, int *counter, int i) {
	if(i%2==0) {
		if(pList->right != pList->tail) {
			(*pList).right->i = -1;
			pList->right = (*pList).right->next;
			(pList->length)++;
		}
	} else {
		if(pList->left != pList->head) {
			(*pList).left->i = -1;
			pList->left = (*pList).left->prev;
			(pList->length)++;
		}
	}
	if (pList->length > BLOCKSIZE) {
		deAllocateBlock(pList, counter, BLOCKSIZE);
	}
}

void clearList(struct list *pList, int *counter) {
	while(pList->right != pList->tail) {
		pullInt(pList, counter, 0);
	}
	while(pList->left != pList->head) {
		pullInt(pList, counter, 1);
	} 
	deAllocateBlock(pList, counter, pList->length);
	freeList(pList, counter);
}

int getInput(char *s) {
	char c;
	int i;
	c = '\0';
	i = 0;
	while (c != '\n' && i < maxInput) {
		c = getchar();
		if (c >= '0' && c <= '9') {
			s[i] = c;
			i++;
		}
	}
	if (i == maxInput) {
		while (c != '\n') {
			c = getchar();
		}
	}
	return i;
}
