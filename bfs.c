// bfs.c
#include <stdlib.h>
#include "bfs.h"
#include "graph.h"
#include "list.h"
#include "queue.h"
 
/**
 * 图应用举例，计算网络跳数。计算从一个结点到另外一个结点的最佳路径
 * 使用广度优先搜索
 * @param  graph 代表整个网络
 * @param  start 代表起始顶点
 * @param  hops  从起始顶点可到达的顶点的链表
 * @return       成功返回0；失败非0
 */
int bfs(Graph *graph, BfsVertex *start, List *hops)
{
	Queue queue;
	AdjList *adjlist, *clr_adjlist;
	BfsVertex *clr_vertex, *adj_vertex;
	ListElmt *element, *member;

	// 初始化图中所有顶点
	for (element = list_head(&graph_adjlists(graph)); element != NULL;
		element = list_next(element)) {
		clr_vertex = ((AdjList *)list_data(element))->vertex;
		// 起始点涂为灰色，其它都涂为白色
		if (graph->match(clr_vertex, start)) {
			clr_vertex->color = gray;
			clr_vertex->hops = 0;
		} else {
			clr_vertex->color = white;
			clr_vertex->hops = -1;
		}
	}

	// 初始化队列，并将起始邻接表放入队列中
	queue_init(&queue, NULL);
	if (graph_adjlist(graph, start, &clr_adjlist) != 0) {
		queue_destroy(&queue);
		return -1;
	}
	if (queue_enqueue(&queue, clr_adjlist) != 0) {
		queue_destroy(&queue);
		return -1;
	}

	// 开始深度优先搜索
	while (queue_size(&queue) > 0) {
		adjlist = queue_peek(&queue);
		// 遍历当前邻接表中的每一个顶点
		for (member = list_head(&adjlist->adjacent); member != NULL;
			member = list_next(member)) {
			adj_vertex = list_data(member);
			// 取出一个邻接表，并修改其顶点的颜色
			if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0) {
				queue_destroy(&queue);
				return -1;
			}
			clr_vertex = clr_adjlist->vertex;

			if (clr_vertex->color == white) {
				clr_vertex->color = gray;
				clr_vertex->hops = ((BfsVertex *)adjlist->vertex)->hops + 1;
				// 将这个邻接表加入队列中
				if (queue_enqueue(&queue, clr_adjlist) != 0) {
					queue_destroy(&queue);
					return -1;
				}
			}
		}
		// 将当前邻接表移除队列，并将其颜色涂为黑色
		if (queue_dequeue(&queue, (void **)&adjlist) == 0) {
			((BfsVertex *)adjlist->vertex)->color = black;
		} else {
			queue_destroy(&queue);
			return -1;
		}
	}

	queue_destroy(&queue);

	list_init(hops, NULL);

	for (element = list_head(&graph_adjlists(graph)); element != NULL;
		element = list_next(element)) {
		clr_vertex = ((AdjList *)list_data(element))->vertex;
		if (clr_vertex->hops != -1) {
			if (list_ins_next(hops, list_tail(hops), clr_vertex) != 0) {
				list_destroy(hops);
				return -1;
			}
		}
	}

	return 0;
}