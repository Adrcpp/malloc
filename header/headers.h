/*
** headers.h for Malloc in /home/adrien/MALLOC/headers
**
** Made by CESARO Adrien
** Login   <cesaro_a@etna-alternance.net>
**
** Started on  Wed Jan 10 05:54:25 2018 CESARO Adrien
** Last update Thu Mar 1 14:38:22 2018 CESARO Adrien
*/


#ifndef _HEADERS_
#define _HEADERS_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define PAGE_SIZE (int) sysconf(_SC_PAGE_SIZE)
#define MAGIC -42
#define TRUE 1
#define FALSE 0
#define UNSET 2

/*
*   Block d'info sur la mémoire. Contient la taille.
*
*   free = 0 : le block est utilisé
*   free = 1 : le block est libre
*
*   les infos sont à la fin du block (c.à.d à (block + 1) )
*
*    b        b + 1
*     __________________________
*    |         |               |
*    | t_block |               |
*    |_________|_______________|
*/
typedef struct s_block {
    unsigned int   size;
    char           magic;
    char           inuse;
    struct s_block *next;
} t_block;

typedef struct s_info_heap {
    unsigned int free_size;
    unsigned int total_size;
    void         *start_heap;
    void         *addr;
} t_info_heap;

/*
*   Tableau contenant la tête des listes chainées
*   des block de mémoires t_block.
*
*   0 -> 16 bytes
*   1 -> 32 bytes
*   2 -> 64 bytes ...
*/
extern t_block *free_list[128];

void heap_init();
int get_rounded_up_size(int size);
t_block *get_free_block(unsigned int size);
void insert_list(t_block *block);
void put_first(t_block *block, int i);
void *malloc(size_t size);
void free(void *ptr);
t_block **get_free_list();
int init_heap();
int get_new_page();
t_block *init_new_block(int rounded_size);
void *calloc(size_t nmemb, size_t size);
void *realloc(void *ptr, size_t size);

#endif
