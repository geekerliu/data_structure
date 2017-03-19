// dfs.h，深度优先例子，拓扑排序
#ifndef DFS_H
#define DFS_H

#include "graph.h"
#include "list.h"

typedef struct DfsVertex_ {
	void *data;
	VertexColor color;
} DfsVertex;

int dfs(Graph *graph, List *ordered);

#endif