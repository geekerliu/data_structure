// ctsort.c
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/**
 * 计数排序
 * @param  data 用于排序的数据，函数返回后，保存排序后的数据
 * @param  size 数据个数
 * @param  k    数据中的最大值
 * @return      成功返回0；失败返回-1
 */
int ctsort(int *data, int size, int k)
{
	int *counts, *temp;
	int i, j;

	if ((counts = (int *)malloc(k * sizeof(int))) == NULL)
		return -1;

	if ((temp = (int *)malloc(size * sizeof(int))) == NULL) {
		free(counts);
		return -1;
	}

	// 初始化计数
	for (i = 0; i < k; i++)
		counts[i] = 0;
	
	// 开始计数
	for (j = 0; j < size; j++)
		counts[data[j]] = counts[data[j]] + 1;

	// 调整计数，使后一个计数包含前面的计数，
	// 这样就确定了每个数的位置
	for (i = 1; i < k; i++)
		counts[i] = counts[i] + counts[i - 1];

	// 将每个数放到对应的位置
	for (j = size - 1; j >= 0; j--) {
		temp[counts[data[j]] - 1] = data[j];
		counts[data[j]] = counts[data[j]] - 1; 
	}

	memcpy(data, temp, size * sizeof(int));

	free(counts);
	free(temp);

	return 0;
}