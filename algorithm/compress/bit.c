// bit.c，位操作

#include "bit.h"

/**
 * 获取某一位的值
 * @param  bits 字符数组
 * @param  pos  位置，从高位开始计算
 * @return      返回该位置的值
 */
int bit_get(const unsigned char *bits, int pos)
{
	unsigned char mask;
	int i;

	mask = 0x80;

	for (i = 0; i < (pos % 8); i++)
		mask = mask >> 1;

	return (mask & bits[pos / 8]) == mask ? 1 : 0;
}
// int bit_get(const unsigned char *bits, int pos)
// {
// 	unsigned char mask;
// 	int i;

// 	mask = 0x01;

// 	for (i = 0; i < (pos % 8); i++)
// 		mask = mask << 1;

// 	return (mask & bits[pos / 8]) == mask ? 1 : 0;
// }

/**
 * 设置某一位的值
 * @param bits  字符数组
 * @param pos   位置
 * @param state 要设置的值
 */
void bit_set(unsigned char *bits, int pos, int state)
{
	unsigned char mask;
	int i;

	mask = 0x80;

	for (i = 0; i < pos % 8; i++)
		mask = mask >> 1;

	if (state)
		bits[pos / 8] = bits[pos / 8] | mask;
	else
		bits[pos / 8] = bits[pos / 8] & (~mask);
}

/**
 * 对bits1和bits2进行异或，结果放在bitsx中，size表示要异或的数据大小。
 * @param bits1 [description]
 * @param bits2 [description]
 * @param bitsx [description]
 * @param size  [description]
 */
void bit_xor(const unsigned char *bits1, const unsigned char *bits2, unsigned
             char *bitsx, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		if (bit_get(bits1, i) != bit_get(bits2, i))
			bit_set(bitsx, i, 1);
		else
			bit_set(bitsx, i, 0);
	}
}

/**
 * 将缓冲区中指定数量的位向左轮转。
 * @param bits  [description]
 * @param size  [description]
 * @param count [description]
 */
void bit_rot_left(unsigned char *bits, int size, int count)
{
	int fbit, lbit, i, j;

	if (size > 0) {
		for (j = 0; j < count; j++) {
			for (i = 0; i <= ((size - 1) / 8); i++) {
				lbit = bit_get(&bits[i], 0);
				if (i == 0) {
					fbit = lbit;
				} else {
					bit_set(&bits[i - 1], 7, lbit);
				}
				bits[i] = bits[i] << 1;
			}

			bit_set(bits, size - 1, fbit);
		}
	}
}
