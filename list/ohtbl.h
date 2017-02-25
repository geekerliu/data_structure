// ohtbl.h
#ifndef OHTBL_H
#define OHTBL_H

#include <stdlib.h>

typedef struct OHTbl_
{
	int positions;// 槽位数目
	void *vacated;

	int (*h1)(const void *key);// 双散列函数
	int (*h2)(const void *key);// 双散列函数
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);

	int size;// 表中现有元素的数量
	void **table;// 存储元素的数组
} OHTbl;

/* public interface */
int ohtbl_init(OHTbl *htbl, int positions, int (*h1)(const void *key),
	int (*h2)(const void *key), int (*match)(const void *key1, const void *key2),
	void (*destroy)(void *data));

void ohtbl_destroy(OHTbl *htbl);
int ohtbl_insert(OHTbl *htbl, const void *data);
int ohtbl_remove(OHTbl *htbl, void **data);
int ohtbl_lookup(const OHTbl *htbl, void **data);
#define ohtbl_size(htbl) ((htbl)->size)

#endif