// queue.c
#include <stdlib.h>

#include "queue.h"

/**
 * 入队
 * @param  queue [description]
 * @param  data  [description]
 * @return       [description]
 */
int queue_enqueue(Queue *queue, const void *data)
{
	return list_ins_next(queue, list_tail(queue), data);
}

/**
 * 出队
 * @param  queue [description]
 * @param  data  [description]
 * @return       [description]
 */
int queue_dequeue(Queue *queue, void **data)
{
	return list_rem_next(queue, NULL, data);
}
