// set.h
#ifndef SET_H
#define SET_H

#include <stdlib.h>
#include "list.h"

typedef List Set;

// public interface
void set_init(Set *set, int (*match)(const void *key1, const void *key2),
	void (*destroy)(void *data));
#define set_destroy list_destroy
int set_insert(Set *set, const void *data);
int set_remove(Set *set, void **data);

/**
 * 计算两个集合的并集
 * @param  setu 合并后的集合
 * @param  set1 用于合并的集合1
 * @param  set2 用于合并的集合2
 * @return      成功返回0；失败返回-1
 */
int set_union(Set *setu, const Set *set1, const Set *set2);

/**
 * 求两个集合的交集
 * @param  seti 交集
 * @param  set1 集合1
 * @param  set2 集合2
 * @return      成功返回0；失败返回-1
 */
int set_intersection(Set *seti, const Set *set1, const Set *set2);

/**
 * 求两个集合的差集
 * @param  setd 差集
 * @param  set1 集合1
 * @param  set2 集合2
 * @return      成功返回0；失败返回-1
 */
int set_difference(Set *setd, const Set *set1, const Set *set2);

int set_is_member(const Set *set, const void *data);
int set_is_subset(const Set *set1, const Set *set2);
int set_is_equal(const Set *set1, const Set *set2);
#define set_size(set) ((set)->size)

#endif