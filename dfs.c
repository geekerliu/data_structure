// dfs.c，深度优先搜索的实现
#include <stdlib.h>
#include "dfs.h"
#include "graph.h"
#include "list.h"

static int dfs_main(Graph *graph, AdjList *adjlist, List *ordered)
{
	AdjList *clr_adjlist;
	DfsVertex *clr_vertex, *adj_vertex;
	ListElmt *member;

	((DfsVertex *)adjlist->vertex)->color = gray;

	for (member = list_head(&adjlist->adjacent); member != NULL;
		member = list_next(member)) {
		adj_vertex = list_data(member);
		if (graph_adjlist(graph, adj_vertex, &clr_adjlist) != 0)
			return -1;

		clr_vertex = clr_adjlist->vertex;
		// 如果当前邻接顶点的颜色是白色，就继续往下一级遍历
		if (clr_vertex->color == white) {
			if (dfs_main(graph, clr_adjlist, ordered) != 0)
				return -1;
		}
	}

	((DfsVertex *)adjlist->vertex)->color = black;
	if (list_ins_next(ordered, NULL, (DfsVertex *)adjlist->vertex) != 0)
		return -1;

	return 0;
}

int dfs(Graph *graph, List *ordered)
{
	DfsVertex *vertex;
	ListElmt *element;

	// 初始化所有的顶点，全部涂为白色
	for (element = list_head(&graph_adjlists(graph)); element != NULL;
		element = list_next(element)) {
		vertex = ((AdjList *)list_data(element))->vertex;
		vertex->color = white;
	}

	list_init(ordered, NULL);
	for (element = list_head(&graph_adjlists(graph)); element != NULL;
		element = list_next(element)) {
		vertex = ((AdjList *)list_data(element))->vertex;

		if (vertex->color == white) {
			if (dfs_main(graph, (AdjList *)list_data(element), ordered) != 0) {
				list_destroy(ordered);
				return -1;
			}
		}
	}

	return 0;
}




