//list.c
#include <stdlib.h>
#include <string.h>

#include "list.h"

/**
 * 初始化链表
 * @param list 要初始化的链表
 * @param destory 如果节点中的数据需要destroy，则提供destroy函数，该函数
 * 在list_destroy中被调用，用于销毁节点中的数据。如果节点中的数据不需要销毁，
 * 则该参数传NULL。
 */
void list_init(List *list, void (*destroy)(void *data))
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
void list_destroy(List *list)
{
	void *data;
	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL) {
			list->destroy(data);
		}
	}
	memset(list, 0, sizeof(List));
}

/**
 * 将元素data插入到链表list的element节点后面。如果element为NULL，
 * 则新的节点插入到链表的开始。
 * @param  list    要操作的链表
 * @param  element 指定的节点
 * @param  data    要插入的数据
 * @return         成功返回0；失败返回-1；
 */
int list_ins_next(List *list, ListElmt *element, const void *data)
{
	ListElmt *new_element;

	if ((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return -1;

	new_element->data = (void*)data;
	if (element == NULL) {
		/* 当链表中没有节点时 */
		if (list_size(list) == 0)
			list->tail = new_element;

		new_element->next = list->head;
		list->head = new_element;
	} else {
		/* 当指定的元素为最后一个节点时 */
		if (element->next == NULL)
			list->tail = new_element;

		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;

	return 0;
}

/**
 * 将节点element从链表list中删除
 * @param  list    要操作的链表
 * @param  element 指定的节点
 * @param  data    用于保存被删除的节点中的数据
 * @return         成功返回0；失败返回-1；
 */
int list_rem_next(List *list, ListElmt *element, void **data)
{
	ListElmt *old_element;

	if (list_size(list) == 0)
		return -1;

	if (element == NULL) {
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if (list_size(list) == 1)
			list->tail = NULL;
	} else {
		if (element->next == NULL)
			return -1;

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		/* 如果移除的是尾节点，调整尾节点 */
		if (element->next == NULL)
			list->tail = element;
	}

	free(old_element);
	list->size--;
	
	return 0;
}