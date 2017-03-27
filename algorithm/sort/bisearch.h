// bisearch.h，二分查找
#ifndef BISEARCH_H
#define BISEARCH_H

int bisearch(void *sorted, const void *target, int size, int esize, int
   (*compare)(const void *key1, const void *key2));

#endif