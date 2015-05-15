/*
Hanyu Xiong
CS449
Project 3


gcc test0.c mymalloc.c -o test0
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

//include your code
#include "mymalloc.h"

//replace malloc here with the appropriate version of mymalloc
#define MALLOC my_worstfit_malloc
//replace free here with the appropriate version of myfree
#define FREE my_free

int main() {
	char *test0;
	char *test2;
	char *test3;
	char *test4;
	char *test5;
	
	printf("\nsbrk = %p:\n\n", sbrk(0));
	
	/*part1 of test1 checks to make sure a node can be freed and if the last node
	is the one freed then shorten the linked list*/
	printf("Test 1.1\n");
		test0 = (char*)MALLOC(50);
		test2 = (char*)MALLOC(40);
		test3 = (char*)MALLOC(100);
		
		printf("test0: %p = 50\n", test0);
		printf("test2: %p = 40\n", test2);
		printf("test3: %p = 100\n", test3);
		print_list();
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("Freeing test0\n");
		FREE(test0);
		printf("Freeing test3\n");
		FREE(test3);
		
		print_list();
		printf("End test 1.1\n");
		printf("sbrk(0): %p\n", sbrk(0));
		printf("\n\n");
	
	/*part2 of test1 checks to make sure if a node of a smaller size is allocated 
	then the node will be split in two one free one not; and that worstfit works by an smaller 
	allocation selecting the free node that has more free space*/
	printf("Test 1.2\n");
		test0 = (char*)MALLOC(10);
		
		printf("test0: %p = 10\n", test0);
		print_list();
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("Freeing test0\n");
		FREE(test0);
		print_list();
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("End test 1.2\n");
		printf("sbrk(0): %p\n", sbrk(0));
		printf("\n\n");
	
	/*part3 of test1 checks to make sure that if more than enough space is allocated
	it will be allocated creating a new node; and that worstfit works by an smaller 
	allocation selecting the free node that has more free space; and that when two 
	adjacent nodes are freed, then they are also merged*/
	printf("Test 1.3\n");
		test4 = (char*)MALLOC(500);
		test5 = (char*)MALLOC(10);
		
		printf("test4: %p = 500\n", test4);
		printf("test5: %p = 10\n", test5);
		print_list();
		
		printf("Freeing test2\n");
		FREE(test2);
		print_list();
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("Freeing test5\n");
		FREE(test5);
		printf("Freeing test4\n");
		FREE(test4);
		
		printf("End test 1.3\n");
		printf("sbrk(0): %p\n", sbrk(0));
		printf("\n\n\n");
	
	/*test2 checks to make sure that when a node with free nodes both in front of
	it and behind it it merges all 3 nodes to free*/
	printf("Test 2.0\n");
		test0 = (char*)MALLOC(50);
		test2 = (char*)MALLOC(40);
		test3 = (char*)MALLOC(700);
		test4 = (char*)MALLOC(500);
		test5 = (char*)MALLOC(100);
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("test0: %p = 50\n", test0);
		printf("test2: %p = 40\n", test2);
		printf("test3: %p = 700\n", test3);
		printf("test4: %p = 500\n", test4);
		printf("test5: %p = 100\n", test5);
		print_list();
		
		printf("Freeing test0\n");
		FREE(test0);
		printf("Freeing test3\n");
		FREE(test3);
		print_list();
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("Freeing test2\n");
		FREE(test2);
		print_list();
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("Freeing test4\n");
		FREE(test4);
		printf("Freeing test5\n");
		FREE(test5);
		printf("sbrk(0): %p\n", sbrk(0));
		
		printf("End test 2.0\n");
		printf("sbrk(0): %p\n", sbrk(0));
		printf("\n\n");

	printf("sbrk = %p:\n", sbrk(0));
	
	return 0;
}
