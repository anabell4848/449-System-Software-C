/*
Hanyu Xiong
CS449
Project 3


gcc mallocdrv.c mymalloc.c -o malloc.drv
*/

void *my_worstfit_malloc(int size);

void my_free(void *ptr);

void print_list();