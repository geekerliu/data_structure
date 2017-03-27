// root.c,方程求解
#include <math.h>
#include "nummeths.h"

/**
 * f:函数f
 * g:函数f的导数
 * x:初始值为x[0],迭代过程中计算出的近似值也都保存在数组x中
 * n:代表迭代的最大次数
 * delta:表示一个可接受的差值
 */
int root(double (*f)(double x), double (*g)(double x), double *x, int *n,
         double delta)
{
	int satisfied, i;

	i = 0;
	satisfied = 0;

	while (!satisfied && i + 1 < *n) {
		// 这是在干什么？？
		x[i + 1] = x[i] - (f(x[i]) / g(x[i]));

		if (fabs(x[i + 1] - x[i]) < delta)
			satisfied = 1;

		i++;
	}

	if (i == 0)
		*n = 1;
	else
		*n = i + 1;

	if (satisfied)
		return 0;
	else
		return -1;
}



