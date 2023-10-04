#include <stdio.h>
#include <stdlib.h>

#ifndef _MEMLAYOUT_H_
#define _MEMLAYOUT_H_

#define MEM_RW 0
#define MEM_RO 1
#define MEM_NO 2

struct memregion {
    void *from;
    void *to;
    unsigned char mode; /* MEM_RW, or MEM_RO, MEM_NO */
};
int get_mem_layout (struct memregion *regions, unsigned int size);

#endif



