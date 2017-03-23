// issort.c，插入排序，时间复杂度O(n*n)
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/**
 * 取出一个结点，与已经排序好的结点对比，然后插入空位中。
 * data：保存已经排好序的元素
 * size: 元素个数
 * esize：每个元素的大小
 * compare：比较函数；在增序中，如果key1>key2，函数返回1；
 * 如果key1=key2，函数返回0；
 * 如果key1<key2，函数返回-1。在递减排序中，返回值相反。
 */
int issort(void *data, int size, int esize, 
	int (*compare)(const void *key1, const void *key2))
{
	char *a = data;
	void *key;
	int i, j;

	if ((key = malloc(esize)) == NULL)
		return -1;

	for (j = 1; j < size; j++) {
		memcpy(key, &a[j * esize], esize);
		i = j - 1;

		while (i >= 0 && compare(&a[i * esize], key) > 0) {
			memcpy(&a[(i + 1) * esize], &a[i * esize], esize);
			i--;
		}
		memcpy(&a[(i + 1) * esize], key, esize);
	}

	free(key);
	return 0;
}















