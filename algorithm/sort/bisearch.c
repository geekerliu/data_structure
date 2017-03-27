// bisearch.c，二分查找
#include <stdlib.h>
#include <string.h>

#include "search.h"

/**
 * sorted:排好序的数组
 * target:要查找的元素
 * size:数组中元素个数
 * esize:数组中单个元素大小
 * compare:用于比较两个元素大小的函数
 */
int bisearch(void *sorted, const void *target, int size, int esize, int
             (*compare)(const void *key1, const void *key2))
{
	int left, middle, right;

	left = 0;
	right = size - 1;

	while (left <= right) {
		middle = (left + right) / 2;

		switch (compare((char *)sorted + (esize * middle), target)) {
		case -1:
			left = middle + 1;
			break;
		case 1:
			right = middle - 1;
			break;
		case 0:
			return middle;
		}
	}

	return -1;
}
