// qksort.c，快速排序
#include <stdlib.h>
#include <string.h>

#include "sort.h"

/**
 * 比较两个整数的大小
 * @param  int1 整数1
 * @param  int2 整数2
 * @return      int1>int2返回1，int1<int2返回-1，相等返回0
 */
static int compare_int(const void *int1, const void *int2)
{
	if (*(const int *)int1 > *(const int *)int2)
		return 1;
	else if (*(const int *)int1 < *(const int *)int2)
		return -1;
	else
		return 0;
}

/**
 * data: 用于排序的数据集合
 * esize：元素大小
 * i:
 * k:
 * compare:比较函数
 * return:返回中间位置
 */
static int partition(void *data, int esize, int i, int k, 
	int (*compare)(const void *key1, const void *key2))
{
	char *a = data;
	void *pval, *temp;
	int r[3];

	if ((pval = malloc(esize)) == NULL)
		return -1;

	if ((temp = malloc(esize)) == NULL) {
		free(pval);
		return -1;
	}
	// 计算中位数
	r[0] = (rand() % (k - i + 1)) + i;
	r[1] = (rand() % (k - i + 1)) + i;
	r[2] = (rand() % (k - i + 1)) + i;
	issort(r, 3, sizeof(int), compare_int);
	memcpy(pval, &a[r[1] * esize], esize);

	i--;
	k++;

	// 开始对比交换左右两边的数据
	while (1) {
		do {
			k--;
		} while (compare(&a[k * esize], pval) > 0);

		do {
			i++;
		} while (compare(&a[i * esize], pval) < 0);

		if (i >= k) {
			break;
		} else {
			memcpy(temp, &a[i * esize], esize);
			memcpy(&a[i * esize], &a[k * esize], esize);
			memcpy(&a[k * esize], temp, esize);
		}
	}

	free(pval);
	free(temp);

	return k;
}

/**
 * i:最左边位置
 * k:最右边位置
 */
int qksort(void *data, int size, int esize, int i, int k, int (*compare)
           (const void *key1, const void *key2))
{
	int j;
	while (i < k) {
		if ((j = partition(data, esize, i, k, compare)) < 0)
			return -1;
		// 排序左边部分
		if (qksort(data, size, esize, i, j, compare) < 0)
			return -1;
		// 排序右边部分
		i = j + 1;
	}
	return 0;
}