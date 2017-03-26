// rxsort.c
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "sort.h"

/**
 * 基数排序。实质是在元素每一位上应用计数排序来对数据集合排序。
 * @param  data 用于排序的数据，函数返回后，里面保存的是排好序的内容。
 * @param  size 元素个数
 * @param  p    每个整数包含的位数？？每个数位数必须一样吗？
 * @param  k    指定的基数
 * @return      成功返回0；失败返回-1
 */
int rxsort(int *data, int size, int p, int k)
{
	int *counts, *temp;
	int index, pval, i, j, n;

	if ((counts = (int *)malloc(k * sizeof(int))) == NULL)
		return -1;

	if ((temp = (int *)malloc(size * sizeof(int))) == NULL) {
		free(counts);
		return -1;
	}
	
	for (n = 0; n < p; n++) {
		for (i = 0; i < k; i++)
			counts[i] = 0;
		// 计算取哪一个位置的数，k的n次方，比如10，100...
		pval = (int)pow((double)k, (double)n);

		// 开始计数
		for (j = 0; j < size; j++) {
			index = (int)(data[j] / pval) % k;
			counts[index] = counts[index] + 1;
		}
		// 开始计算每个元素的偏移量
		for (i = 1; i < k; i++)
			counts[i] = counts[i] + counts[i - 1];

		// 开始排序
		for (j = size - 1; j >= 0; j--) {
			index = (int)(data[j] / pval) % k;
			temp[counts[index] - 1] = data[j];
			counts[index] = counts[index] - 1;
		}

		memcpy(data, temp, size * sizeof(int));
	}

	free(counts);
	free(temp);
	return 0;
}