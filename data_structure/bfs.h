// bfs.h
#ifndef BFS_H
#define BFS_H

#include "graph.h"
#include "list.h"

typedef struct BfsVertex_
{
	void *data;//数据域指针
	VertexColor color;//搜索过程中维护顶点的颜色
	int hops;//维护从起始结点开始到顶点的跳数统计
} BfsVertex;

int bfs(Graph *graph, BfsVertex *start, List *hops);

#endif