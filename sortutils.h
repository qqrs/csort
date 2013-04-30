#ifndef SORTUTILS_H
#define SORTUTILS_H

#include "sort.h"

int cmplist(const void *a, const void *b, uint32_t len, uint32_t esize, 
            cmpfn_t cmp);

//int compare(const int *a, const int *b);
void swap(void *a, void *b, void *temp, uint32_t esize);
void copy(void *dest, void *src, uint32_t esize);
void printl( int *base, uint32_t len, uint32_t esize );

// sort using stdlib qsort
void stdsort( int *base, uint32_t len, uint32_t esize, cmpfn_t cmp );

int cmpint(const void *a, const void *b);
int cmpint64(const void *a, const void *b);
int cmp10ints(const void *a, const void *b);
int cmpstr(const void *a, const void *b);


#ifdef DEBUG
#define dbgprintl printl
#define dbgprintf printf
#else
#define dbgprintl(a,b,c) do {} while (0)
#define dbgprintf(...) do {} while (0)
#endif

#endif
