// graph.c

#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "list.h"
#include "set.h"

void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2),
                void (*destroy)(void *data))
{
	graph->vcount = 0;
	graph->ecount = 0;
	graph->match = match;
	graph->destroy = destroy;

	list_init(&graph->adjlists, NULL);
}

void graph_destroy(Graph *graph)
{
	AdjList *adjlist;

	while (list_size(&graph->adjlists) > 0) {
		if (list_rem_next(&graph->adjlists, NULL, (void **)&adjlist) == 0) {
			set_destroy(&adjlist->adjacent);

			if (graph->destroy != NULL) {
				graph->destroy(adjlist->vertex);
			}

			free(adjlist);
		}
	}

	list_destroy(&graph->adjlists);
	memset(graph, 0, sizeof(Graph));
}

// 将一个顶点插入图中
int graph_ins_vertex(Graph *graph, const void *data)
{
	ListElmt *element;
	AdjList *adjlist;
	int retval;

	// 不允许插入相同的顶点
	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (graph->match(data, ((AdjList *)list_data(element))->vertex))
			return 1;
	}

	if ((adjlist = (AdjList *)malloc(sizeof(AdjList))) == NULL)
		return -1;

	adjlist->vertex = (void *)data;
	set_init(&adjlist->adjacent, graph->match, NULL);

	if ((retval = list_ins_next(&graph->adjlists, list_tail(&graph->adjlists),
	                            adjlist)) != 0) {
		return retval;
	}

	graph->vcount++;
	return 0;
}

//将一条边插入图中
int graph_ins_edge(Graph *graph, const void *data1, const void *data2)
{
	ListElmt *element;
	int retval;

	// 确保两个顶点都在图中
	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (graph->match(data2, ((AdjList *)list_data(element))->vertex))
			break;
	}

	if (element == NULL)
		return -1;

	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (graph->match(data1, ((AdjList *)list_data(element))->vertex))
			break;
	}

	if (element == NULL)
		return -1;

	// 把data2放到data1的集合中去，即插入一条边
	if ((retval = set_insert(&((AdjList *)list_data(element))->adjacent, data2)) != 0)
		return retval;

	graph->ecount++;
	return 0;
}

// 移除一个顶点
int graph_rem_vertex(Graph *graph, void **data)
{
	ListElmt *element, *temp, *prev;
	AdjList *adjlist;
	int found;

	prev = NULL;
	found = 0;

	// 为什么这个循环里面没有break，一定要轮询完吗？？
	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (set_is_member(&((AdjList *)list_data(element))->adjacent, *data))
			return -1;

		if (graph->match(*data, ((AdjList *)list_data(element))->vertex)) {
			temp = element;
			found = 1;
		}

		if (!found)
			prev = element;
	}

	// 未找到该顶点
	if (!found)
		return -1;

	// 如果这个顶点的邻接表不是空，则不允许移除这个顶点
	if (set_size(&((AdjList *)list_data(temp))->adjacent) > 0)
		return -1;

	// 移除顶点
	if (list_rem_next(&graph->adjlists, prev, (void **)&adjlist) != 0)
		return -1;

	*data = adjlist->vertex;
	free(adjlist);

	graph->vcount--;
	return 0;
}

// 移除一条边
int graph_rem_edge(Graph *graph, void *data1, void **data2)
{
	ListElmt *element;

	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (graph->match(data1, ((AdjList *)list_data(element))->vertex))
			break;
	}

	if (element == NULL)
		return -1;

	// 把data1到data2的那条边移除
	if (set_remove(&((AdjList *)list_data(element))->adjacent, data2) != 0)
		return -1;

	graph->ecount--;
	return 0;
}

// 获取指定顶点的邻接表
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist)
{
	// prev这个指针有卵用？
	ListElmt *element, *prev;

	prev = NULL;
	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (graph->match(data, ((AdjList *)list_data(element))->vertex))
			break;

		prev = element;
	}

	if (element == NULL)
		return -1;

	*adjlist = list_data(element);
	return 0;
}

// 判断指定的两个顶点是否有邻接关系
int graph_is_adjacent(const Graph *graph, const void *data1,
                      const void *data2)
{
	// prev这个指针有卵用？
	ListElmt *element, *prev;

	prev = NULL;
	for (element = list_head(&graph->adjlists); element != NULL;
	     element = list_next(element)) {
		if (graph->match(data1, ((AdjList *)list_data(element))->vertex))
			break;

		prev = element;
	}

	if (element == NULL)
		return -1;

	return set_is_member(&((AdjList *)list_data(element))->adjacent, data2);
}
