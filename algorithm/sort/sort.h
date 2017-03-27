#ifndef SORT_H
#define SORT_H

// 插入排序
int issort(void *data, int size, int esize, int (*compare)(const void *key1,
           const void *key2));

// 快速排序
int qksort(void *data, int size, int esize, int i, int k, int (*compare)
           (const void *key1, const void *key2));

// 归并排序
int mgsort(void *data, int size, int esize, int i, int k, int (*compare)
           (const void *key1, const void *key2));

// 计数排序
int ctsort(int *data, int size, int k);

// 基数排序
int rxsort(int *data, int size, int p, int k);

#endif