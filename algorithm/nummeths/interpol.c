// interpol.c,多项式插值的实现
#include <stdlib.h>
#include <string.h>

#include "nummeths.h"

/**
 * 采用多项式插值法求得函数在某些特定点上的值
 * @param  x  函数已知的点集
 * @param  fx 每个已知点集对应的函数值
 * @param  n  已知点集的个数
 * @param  z  待求得点集
 * @param  pz 待求点集得到的值
 * @param  m  待求点集个数
 * @return    成功返回0；失败返回-1
 */
int interpol(const double *x, const double *fx, int n, double *z,
	double *pz, int m)
{
	// coeff用来保存系数
	double term, *table, *coeff;
	int i, j, k;

	if ((table = (double *)malloc(sizeof(double) * n)) == NULL)
		return -1;

	if ((coeff = (double *)malloc(sizeof(double) * n)) == NULL) {
		free(table);
		return -1;
	}

	// 给第一行赋值
	memcpy(table, fx, sizeof(double) * n);
	coeff[0] = table[0];

	// 计算每一层的系数
	for (k = 1; k < n; k++) {
		for (i = 0; i < n - k; i++) {
			j = i + k;
			table[i] = (table[i + 1] - table[i]) / (x[j] - x[i]); 
		}
		coeff[k] = table[0];
	}
	free(table);

	// 计算指定的z点的值
	for (k = 0; k < m; k++) {
		pz[k] = coeff[0];
		for (j = 1; j < n; j++) {
			term = coeff[j];
			for (i = 0; i < j; i++)
				term = term * (z[k] - x[i]);

			pz[k] = pz[k] + term;
		}
	}

	free(coeff);
	return 0;
}



