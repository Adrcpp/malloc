/*
** malloc.c for Malloc in /home/adrien/MALLOC
**
** Made by CESARO Adrien
** Login   <cesaro_a@etna-alternance.net>
**
** Started on  Wed Jan 10 05:54:25 2018 CESARO Adrien
** Last update Thu Mar 1 14:38:22 2018 CESARO Adrien
*/

#include "./header/headers.h"

t_block *free_list[128] = {NULL};
t_info_heap *_heap = NULL;

t_block **get_free_list()
{
    return free_list;
}

void *malloc(size_t size)
{
    if (!size || size < 1)
    {
        if (DEBUG)
            printf("\n ************ / ! \\ **** MALLOC null or size 0: **** / ! \\ ************ \n");
        return NULL;
    }

    if (!_heap)
        if (init_heap() == 0)
            return NULL;

    int rounded_size = get_rounded_up_size(size);

    if (DEBUG)
        printf("\n --* * Requested memory : %d * *--\n", rounded_size);

    t_block *block = get_free_block(rounded_size);

    if (block)
        return (block + 1);

    if (_heap->free_size <= (unsigned int) rounded_size + sizeof(t_block))
        if (get_new_page(rounded_size) == 0)
            return NULL;

    if ( (block = init_new_block(rounded_size)) == NULL)
        return NULL;

    if (DEBUG)
        printf("\n**********************\n");

    return (block + 1);
}

t_block *init_new_block(int rounded_size)
{
    t_block *block = NULL;

    block = (_heap->addr);
    block->size = rounded_size;
    block->magic = MAGIC;
    block->inuse = UNSET;
    block->next = NULL;

    _heap->addr = (_heap->addr + sizeof(t_block) + rounded_size);
    _heap->free_size -= (rounded_size + sizeof(t_block));

    if (DEBUG)
    {
        printf(" address of block: %p \n", _heap->addr);
        printf(" address end : %p \n", _heap->addr);
        printf(" free_size : %d \n", _heap->free_size);
    }

    return block;
}

int init_heap()
{
    if (DEBUG)
        printf("\n******* INIT HEAP *********\n");

    void *start = sbrk(0);

    _heap = sbrk(PAGE_SIZE);
    if (_heap == (void *) -1)
        return 0;

    _heap->free_size = PAGE_SIZE - sizeof(t_info_heap);
    _heap->total_size = PAGE_SIZE;
    _heap->start_heap = start;

    _heap->addr = ( _heap + (sizeof(t_info_heap*)/sizeof(void *)) );

    if (DEBUG)
    {
        printf(" free_size : %d \n", _heap->free_size);
        printf(" start address : %p \n", _heap->start_heap);
        printf(" limit : %p \n", (_heap->addr + _heap->free_size) );
    }
    return 1;
}

int get_new_page(int size)
{
    int count = 1;
    int res = 0;

    while ( (res = (PAGE_SIZE * count)) < size + (int) sizeof(t_block))
        ++count;

    _heap->addr = sbrk(PAGE_SIZE * count);
    if (_heap->addr == (void *) -1)
        return 0;
        
    _heap->free_size = (PAGE_SIZE * count);
    _heap->total_size += (PAGE_SIZE * count);

    if (DEBUG)
    {
        printf("\n******* NEW PAGE *********\n");
        printf(" free_size : %d  \n", _heap->free_size);
        printf(" total_size : %d  \n", _heap->total_size);
    }
    return 1;
}

/*
*   TODO: parcourir la liste de
*   block à la recherche d'un block libre
*   de taille 'size'
*/
t_block *get_free_block(unsigned int size)
{
    t_block *temp;

    //int index = (size / 8);
    int index = (int) log2((double) size);

    if ((temp = free_list[index]) == NULL)
      return NULL;

    if (DEBUG)
        printf("*** get free block ****\n");

    while (temp != NULL)
    {
      if (temp->size == size && temp->inuse == FALSE)
      {
         temp->inuse = TRUE;

         if (DEBUG)
            printf("Returning block of size %d \n", temp->size);

         return (temp);
      }

      if (DEBUG)
        printf(" next \n");
      temp = temp->next;
    }

    if (DEBUG)
        printf("*** block not found ****\n");
    return NULL;
}

/*
*   Arrondi la taille du block
*   à une puissance de 2
*/
int get_rounded_up_size(int size)
{
    int power = 1;

    if (size <= 16)
        return 16;

    while (power < size)
        power *= 2;

    return power;
}

/*
*   Insère le block nouvellement créé
*   au début de la liste
*/
void insert_list(t_block *block)
{
    //int index = (block->size / 8) - 2;
    int index = (int) log2( (double) block->size);

    if (free_list[index])
    {
        if (DEBUG)
        {
            printf(" \n ***** FREE ******");
            printf("\n put first block %d", block->size);
            printf("\n index %d\n", index);
        }

        if (block->inuse == UNSET)
            put_first(block, index);
    }
    else
    {
        if (DEBUG)
        {
            printf(" \n ***** FREE ******");
            printf("\n new list head %d", block->size);
            printf("\n index %d\n", index);
        }

        free_list[index] = block;
    }
    block->inuse = FALSE;
}

/*
*   Insère le block dans la bonne liste
*   à l'index i
*/
void put_first(t_block *block, int i)
{
    block->next = free_list[i];
    free_list[i] = block;
}

/*
*  Controle si le pointeur à été alloué par
*  malloc et qu'il appartient à la heap.
*  Met dans la bonne liste chainée le pointeur.
*
*/
void free(void *ptr)
{
    t_block *block;

    if (ptr == NULL)
        return;

    block = ( ((t_block *) ptr) - 1);

    if (block->magic != MAGIC)
    {
        printf("\n*** invalid pointers: %p *** \n",  block);
        exit(EXIT_FAILURE);
    }

    if (block->inuse == FALSE)
    {
        printf("\n*** double free or corruption: %p *** \n", block);
        exit(EXIT_FAILURE);
    }
    insert_list(block);
}

/*
*  Alloue de la memoire pour nnemb élément
*  de taille size.
*  initie à zéro la mémoire allouée.
*
*/
void *calloc(size_t nmemb, size_t size)
{
    void *test = NULL;

    if (DEBUG)
    {
        printf("\n*** CALLOC of size %d *** \n", (int) size);
        printf(" number of element : %d \n", (int) nmemb);
    }

    test = malloc(size * nmemb);
    memset(test, 0,size * nmemb);

    return test;
}

/*
*  Augmente la mémoire du pointeur ptr
*  jusqu'à la taille size.
*  Si pointeur null alors equivalent à un malloc
*  sinon réécris les données à l'adresse du nouveau pointeur
*/
void *realloc(void *ptr, size_t size)
{

    void *test = NULL;

    if (DEBUG)
    {
        printf("\n*** realloc of size %d *** \n", (int) size);
        printf(" address ptr : %p \n", ptr);
    }

    if (!ptr)
    {
        if (DEBUG)
            printf(" null pointer \n");
        test = malloc(size);
    }
    else
    {
        if (DEBUG)
        {
            t_block  *block = ( ((t_block *) ptr) - 1);
            printf("\n address block : %p \n", block);
            printf("  old block size : %d \n", block->size);
        }

        test = malloc(size);
        memmove(test, ptr, size);
        free(ptr);
        return test;
    }
    return test;
}
