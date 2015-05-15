/*
Hanyu Xiong
CS449
Project 3

*/
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h> 
#include <unistd.h>

typedef struct node {
	int size; 
	int inuse; 		//1 if being used
	struct node *next;
	struct node *prev;
} node;

node *root;
node *end;

void* my_worstfit_malloc (int size) {
	void *ptr;
	
	ptr=NULL;		//ptr starts as NULL and if not changed it will return as null
	
	if (root == NULL) {
		node newnode;
		
		newnode.size = size;
		newnode.inuse = 1;
		newnode.next = NULL;
		newnode.prev = NULL;
		
		root = (node*) sbrk(size + sizeof(node));
		//Initializing linked list at root
		*root = newnode;
		end = root;
		
		ptr= root + 1;
	}
	else {
		node *worst;
		node *cur;
		
		worst=NULL;
		cur=root;
		
		//Searching for worst fit node
		while (cur->next != NULL) {
			if (cur->size >= size && cur->inuse == 0 && (worst == NULL || cur->size > worst->size)) {
				worst = cur;
			}
			//printf("Current Node: %p Size: %d Used: %d Previous: %p Next: %p\n", cur,cur->size,cur->inuse,cur->prev,cur->next);
			cur = cur->next;
			
			
		}
		
		if (worst != NULL) {	//found a worst node to allocate
			cur = worst;
			//Selecting a free node of cur size
			if (cur->size - size > sizeof(node)){
				//Free node has enough space remaining for a new node, splitting it into two nodes
				//(cur->size) bytes free in cur, creating new node of remaining size
				worst = (node*)(((char*)cur) + size + sizeof(node));

				if (cur->next == NULL) {
					end = worst;
				}
				
				node newnode;
	
				newnode.size = cur->size - size - sizeof(node);
				newnode.inuse = 0;
				newnode.next = cur->next;
				newnode.prev = cur;

				*worst = newnode;

				if (cur->next != NULL) {
					cur->next->prev = worst;
				}
				cur->size = size;
				cur->inuse = 1;
				cur->next = worst;
			}
			else {
				//Free node doesn't have enough remaining space for another node, allocating it entirely
				cur->inuse = 1;
			}
			ptr=cur + 1;
		}
		else {	//Couldn't find any free nodes, so we check end node
			if (end->inuse == 0) { //if end node is free, we extend it
				sbrk(size - end->size);
				end->size = size;
				end->inuse = 1;
				
				ptr=end + 1;
			}
			else { //Last node is not free, allocating a new one after it
				node newnode;
				
				newnode.size = size;
				newnode.inuse = 1;
				newnode.next = NULL;
				newnode.prev = end;
				
				worst = (node*) sbrk(size + sizeof(node));
				*worst = newnode;
				end->next = worst;
				end = worst;
				
				ptr=worst + 1;
			}
		}
	}
	return ptr;
}

void my_free (void *ptr) {
	node *freeb;
	node *nextb;
	node *prevb;	
	freeb = (node*)ptr - 1;
	
	if (ptr != (void*)NULL) {
		if (freeb->inuse == 0) {	//node already free
			return;
		}
		else {
			//set node to be free
			freeb->inuse = 0;
			nextb=freeb->next;
			prevb=freeb->prev;
			
			if (nextb != NULL && nextb->inuse == 0) { //Next node is free, coalesce			
				freeb->size += sizeof(node) + nextb->size;
				freeb->next = nextb->next;
				if (freeb->next != NULL) {
					freeb->next->prev = freeb;
				}
			}
			if (prevb != NULL && prevb->inuse == 0) {	//Previous node is free, coalesce
				prevb->size += sizeof(node) + freeb->size;
				prevb->next = freeb->next;
				if (freeb->next != NULL) {
					freeb->next->prev = prevb;
				}
				if (freeb == end) {
					end = prevb;
				}
				freeb = prevb;
			}
			if (freeb->next == NULL){
				if (freeb->prev == NULL) { //only node in the list, reset linked list
					root = NULL;
					end = NULL;
				}
				else{	//node is the end node, releasing memory
					freeb->prev->next = NULL;
					end = freeb->prev;
				}
				sbrk(0-(freeb->size+ sizeof(node)));
				return;
			}
		}
	}
}

//for debugging purposes
void print_list(){
	printf("Linked list of nodes:\n");
	node *testing;
	testing = root;
	while(testing != NULL) {
		printf("Node: %p Size: %d Used: %d Previous: %p Next: %p\n", testing,testing->size,testing->inuse,testing->prev,testing->next);
		testing = testing->next;
	}
}