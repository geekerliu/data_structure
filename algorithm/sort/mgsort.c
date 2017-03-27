// mgsort.c,归并排序实现

#include <stdlib.h>
#include <string.h>
#include "sort.h"

/**
 * 将两个有序集合并为一个
 * data:有序集
 * esize:单个元素大小
 * i:左边集合的开始位置
 * j:中间位置
 * k:右边集合的最后位置
 * compare:用户传入得用于比较两个数据大小的函数
 */
static int merge(void *data, int esize, int i, int j, int k, 
	int (*compare)(const void *key1, const void *key2))
{
	char *a = data, *m;
	int ipos, jpos, mpos;

	ipos = i;// 指向左边集合
	jpos = j + 1;// 指向右边集合
	mpos = 0;// 记录现在已经排序好的元素的位置

	if ((m = (char *)malloc(esize * ((k - i) + 1))) == NULL)
		return -1;

	while (ipos <= j || jpos <= k) {
		if (ipos > j) {
			// 左边的已经全部被和并了，现在开始把右边的全部合并
			while (jpos <= k) {
				memcpy(&m[mpos * esize], &a[jpos * esize], esize);
				jpos++;
				mpos++;
			}
			break;
		} else if (jpos > k) {
			// 右边的已经全部被和并了，现在开始把左边的全部合并
			while (ipos <= j) {
				memcpy(&m[mpos * esize], &a[ipos * esize], esize);
				ipos++;
				mpos++;
			}
			break;
		}

		if (compare(&a[ipos * esize], &a[jpos * esize]) < 0) {
			memcpy(&m[mpos * esize], &a[ipos * esize], esize);
			ipos++;
			mpos++;
		} else {
			memcpy(&m[mpos * esize], &a[jpos * esize], esize);
			jpos++;
			mpos++;
		}
	}

	memcpy(&a[i * esize], m, esize * ((k - i) + 1));

	free(m);

	return 0;
}

/**
 * data:data最初包含size个无序元素
 * size:元素个数
 * esize:单个元素的大小
 * i:开始时i设置为0
 * k:开始时k设置为size-1
 * compare:用户传入得用于比较两个数据大小的函数
 */
int mgsort(void *data, int size, int esize, int i, int k, int (*compare)
           (const void *key1, const void *key2))
{
	int j;
	if (i < k) {
		j = (int)(((i + k - 1)) / 2);

		if (mgsort(data, size, esize, i, j, compare) < 0)
			return -1;

		if (mgsort(data, size, esize, j + 1, k, compare) < 0)
			return -1;

		if (merge(data, esize, i, j, k, compare) < 0)
			return -1;
	}
	return 0;
}
