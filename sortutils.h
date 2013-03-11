#ifndef SORTUTILS_H
#define SORTUTILS_H

int compare(const int *a, const int *b);
void swap(int *a, int *b);
void printl( int *list, uint32_t size );

// sort using stdlib qsort
void stdsort( int *list, uint32_t size );
int cmpint(const void *a, const void *b);

#ifdef DEBUG
#define dbgprintl printl
#define dbgprintf printf
#else
#define dbgprintl(a,b) do {} while (0)
#define dbgprintf(...) do {} while (0)
#endif

#endif
