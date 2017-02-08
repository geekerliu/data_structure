/**
 * 双向链表
 */
#include <stdlib.h>
#include <string.h>

#include "dlist.h"

void dlist_init(DList *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

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

int dlist_ins_next(DList *list, DListElmt *element, const void *data)
{
	DListElmt *new_element;

	if (element == NULL && dlist_size(list) != 0)
		return -1;

	return 0;
}

int dlist_ins_prev(DList *list, DListElmt *element, const void *data)
{
	return 0;
}

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
