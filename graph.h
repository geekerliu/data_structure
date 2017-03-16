// graph.h
#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>
#include "list.h"
#include "set.h"

// 邻接表定义
typedef struct AdjList_ {
	void *vertex;//顶点
	Set adjacent;//与该顶点相邻接的顶点的集合
} AdjList;

typedef struct Graph_ {
	int vcount;// 顶点计数
	int ecount;// 边计数

	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);

	List adjlists;
} Graph;

typedef enum VertexColor_ {white, gray, black} VertexColor;

void graph_init(Graph *graph, int (*match)(const void *key1, const void *key2),
	void (*destroy)(void *data));
void graph_destroy(Graph *graph);
// 将一个顶点插入图中
int graph_ins_vertex(Graph *graph, const void *data);
//将一条边插入图中
int graph_ins_edge(Graph *graph, const void *data1, const void *data2);
// 移除一个顶点
int graph_rem_vertex(Graph *graph, void **data);
// 移除一条边
int graph_rem_edge(Graph *graph, void *data1, void **data2);
// 获取指定顶点的邻接表
int graph_adjlist(const Graph *graph, const void *data, AdjList **adjlist);
// 判断指定的两个顶点是否有邻接关系
int graph_is_adjacent(const Graph *graph, const void *data1, const void *data2);
#define graph_adjlists(graph) ((graph)->adjlists)
#define graph_vcount(graph) ((graph)->vcount)
#define graph_ecount(graph) ((graph)->ecount)


#endif