// bistree.h，二叉搜索树
// 这是一种专门用于查找操作的二叉树。
// 保持一棵树的平衡是指对于给定数量的结点，要使得树的高度尽可能短。
#ifndef BISTREE_H
#define BISTREE_H

#include "bitree.h"

// 平衡因子定义
#define AVL_LFT_HEAVY 1
#define AVL_BALANCED 0
#define AVL_RGT_HEAVY -1

typedef struct AvlNode_
{
	void *data;
	int hidden;//标志该节点已经移除
	int factor;//平衡因子
} AvlNode;

typedef BiTree BisTree;

// public interface
void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2),
	void (*destroy)(void *data));
void bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bitree_lookup(BisTree *tree, void **data);
#define bistree_size(tree) ((tree)->size)

#endif