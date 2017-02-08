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
	return 0;
}
