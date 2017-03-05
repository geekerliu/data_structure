// ohtbl.c开地址哈希表
#include <stdlib.h>
#include <string.h>

#include "ohtbl.h"

static char vacated;

int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key),
	int (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
	void (*destroy)(void *data))
{
	int i;
	if ((htbl->table = (void **)malloc(positions * sizeof(void *))) == NULL) {
		return -1;
	}

	htbl->positions = positions;
	for (i = 0; i < htbl->positions; i++)
		htbl->table[i] = NULL;

	htbl->vacated = &vacated;

	htbl->h1 = h1;
	htbl->h2 = h2;
	htbl->match = match;
	htbl->destroy = destroy;

	htbl->size = 0;

	return 0;
}

void ohtbl_destroy(OHTbl *htbl)
{
	int i;
	if (htbl->destroy != NULL) {
		for (i = 0; i < htbl->positions; i++) {
			if (htbl->table[i] != NULL && htbl->table[i] != htbl->vacated)
				htbl->destroy(htbl->table[i]);
		}
	}

	free(htbl->table);
	memset(htbl, 0, sizeof(OHTbl));
}

/**
 * 将数据data插入htbl中
 * 
 * @param  htbl 哈希表
 * @param  data 要插入的数据
 * @return      成功返回0，已经存在该数据返回1，其它情况返回-1
 */
int ohtbl_insert(OHTbl *htbl, const void *data)
{
	void *temp;
	int position, i;

	// 没有空间了
	if (htbl->size == htbl->positions)
		return -1;

	temp = (void *)data;
	// 如果已经存在该元素，直接返回
	if (ohtbl_lookup(htbl, &temp) == 0)
		return 1;

	for (i = 0; i < htbl->positions; i++) {
		position = (htbl->h1(data) + (i * htbl->h2(data))) % htbl->positions;

		if (htbl->table[position] == NULL 
			|| htbl->table[position] == htbl->vacated) {
			htbl->table[position] = (void *)data;
			htbl->size++;
			return 0;
		}
	}

	return -1;
}

/**
 * 将数据data从哈希表htbl中移除
 * @param  htbl 哈希表
 * @param  data 要移除的数据
 * @return      成功返回0，失败返回-1
 */
int ohtbl_remove(OHTbl *htbl, void **data)
{
	int position, i;

	for (i = 0; i < htbl->positions; i++) {
		position = (htbl->h1(data) + (i * htbl->h2(*data))) % htbl->positions;

		if (htbl->table[position] == NULL) {
			return -1;
		}  // 该位置的数据已经被删除了，但是仍然需要遍历完才能知道是否还有其它位置有数据
		else if (htbl->table[position] == htbl->vacated) {
			continue;
		} else if (htbl->match(htbl->table[position], *data)) {
			*data = htbl->table[position];
			htbl->table[position] = htbl->vacated;
			htbl->size--;
			return 0;
		}
	}

	return -1;
}

int ohtbl_lookup(const OHTbl *htbl, void **data)
{
	int position, i;

	for (i = 0; i < htbl->positions; i++) {
		position = (htbl->h1(data) + (i * htbl->h2(*data))) % htbl->positions;

		if (htbl->table[position] == NULL) {
			return -1;
		} else if (htbl->match(htbl->table[position], *data)) {
			// 为什么要给data再赋值
			*data = htbl->table[position];
			return 0;
		}
	}
	return -1;
}


