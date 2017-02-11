/**
 * 双向链表,dlist.c
 */
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

/**
 * 初始化链表
 * @param list 要初始化的链表
 * @param destory 指定一个销毁数据的函数，该函数会在dlist_destroy中调用。
 */
void dlist_init(DList *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

/**
 * 销毁链表
 * @param list 要销毁的链表
 */
void dlist_destroy(DList *list)
{
	void *data;
	while (dlist_size(list) > 0) {
		if (dlist_remove(list, dlist_tail(list), (void **)&data) == 0 
			&& list->destroy != NULL) {
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(DList));
}

/**
 * 将元素插入由list指定的双向链表中element元素之后。如果element为NULL。
 * 则将元素插入到链表的开始位置。新的元素包含一个指向data的指针，因此只要
 * 该元素仍在链表中，data所引用的内存空间就应该保持合法。由调用者负责管理
 * data所引用的存储空间。
 * @param  list    要操作的链表
 * @param  element 指定的节点
 * @param  data    要插入的元素
 * @return         成功返回0，失败返回-1
 */
int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
	DListElmt *new_element;

	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	new_element->data = (void *)data;
	if (element == NULL) {
		if (dlist_size(list) == 0) {
			new_element->next = NULL;
			new_element->prev = NULL;
			list->head = new_element;
			list->tail = new_element;
		} else {
			new_element->next = list->head;
			new_element->prev = NULL;
			list->head->prev = new_element;
			list->head = new_element;
		}
	} else {
		new_element->next = element->next;
		new_element->prev = element;

		if (element->next == NULL)
			list->tail = new_element;
		else
			element->next->prev = new_element;

		element->next = new_element;
	}
	list->size++;

	return 0;
}

/**
 * 将元素插入由list指定的双向链表中element元素之前。如果element为NULL。
 * 则将元素插入到链表的开始位置。新的元素包含一个指向data的指针，因此只要
 * 该元素仍在链表中，data所引用的内存空间就应该保持合法。由调用者负责管理
 * data所引用的存储空间。
 * @param  list    要操作的链表
 * @param  element 指定的节点
 * @param  data    要插入的元素
 * @return         成功返回0，失败返回-1
 */
int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
	DListElmt *new_element;

	if ((new_element = (DListElmt *)malloc(sizeof(DListElmt))) == NULL)
		return -1;

	if (element == NULL) {
		if (dlist_size(list) == 0) {
			list->head = new_element;
			list->tail = new_element;
			new_element->next = NULL;
			new_element->prev = NULL;
		} else {
			new_element->next = list->head;
			new_element->prev = NULL;
			list->head->prev = new_element;
			list->head = new_element;
		}
	} else {
		new_element->next = element;
		new_element->prev = element->prev;
		if (element->prev == NULL)
			list->head = new_element;
		else
			element->prev->next = new_element;
		element->prev = new_element;
	}

	return 0;
}

/**
 * 将元素element从链表中移除
 * @param  list    要操作的链表
 * @param  element 要从链表中移除的节点
 * @param  data    移除的节点中的数据
 * @return         成功返回0；失败返回-1。
 */
int dlist_remove(DList *list, DListElmt *element, void **data)
{
	if (element == NULL || dlist_size(list) == 0)
		return -1;

	*data = element->data;
	if (element == list->head) {
		list->head = element->next;

		if (list->head == NULL)
			list->tail = NULL;
		else
			element->next->prev = NULL;
	} else {
		// 将前一个节点的next指向当前节点的下一个节点
		element->prev->next = element->next;
		// 如果这个节点是最后一个节点，删除后，将尾指针指向当前节点的前一个节点；
		// 如果不是最后一个节点，则将后一个节点的prev指向当前节点的前一个节点。
		if (element->next == NULL)
			list->tail = element->prev;
		else
			element->next->prev = element->prev;
	}

	free(element);

	list->size--;

	return 0;
}
