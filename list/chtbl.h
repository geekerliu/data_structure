// chtbl.h 链式哈希表
#ifndef CHTBL_H
#define CHTBL_H

#include <stdlib.h>
#include "list.h"

// define for chained hash tables
typedef struct CHTbl_
{
	int buckets;// 桶的个数
	int (*h)(const void *key);// 用户定义的哈希函数
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);

	int size;// 表中现有元素的个数
	List *table;// 保存桶的链表
} CHTbl;

// public interface
int chtbl_init(CHTbl *htbl, int buckets, int (*h)(const void *key),
	int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));
void chtbl_destroy(CHTbl *htbl);
int chtbl_insert(CHTbl *htbl, const void *data);
int chtbl_remove(CHTbl *htbl, void **data);
int chtbl_lookup(const CHTbl *htbl, void **data);
#define chtbl_size(htbl) ((htbl)->size)

#endif
