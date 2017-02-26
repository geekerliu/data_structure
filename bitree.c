// bitree.c
#include <stdlib.h>
#include <string.h>
#include "bitree.h"

void bitree_init(BiTree *tree, void (*destroy)(void *data))
{
	tree->size = 0;
	tree->destroy = destroy;
	tree->root = NULL;
}

void bittree_destroy(BiTree *tree)
{
	bitree_rem_left(tree, NULL);
	memset(tree, 0, sizeof(BiTree));
}

/**
 * 在指定节点的左边插入一个结点，如果指定的结点为NULL并且树的大小为0，则在根结点插入
 * 
 * @param  tree 树
 * @param  node 指定的结点
 * @param  data 要插入的数据
 * @return      成功返回0，失败返回-1
 */
int bitree_ins_left(BiTree *tree, BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node, **position;

	if (node == NULL) {
		if (bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	} else {
		if (bitree_left(node) != NULL)
			return -1;
		position = &node->left;
	}
	if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
		return -1;

	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	tree->size++;

	return 0;
}

/**
 * 在指定节点的右边插入一个结点，如果指定的结点为NULL并且树的大小为0，则在根结点插入
 * 
 * @param  tree 树
 * @param  node 指定的结点
 * @param  data 要插入的数据
 * @return      成功返回0，失败返回-1
 */
int bitree_ins_right(BiTree *tree, BiTreeNode *node, const void *data)
{
	BiTreeNode *new_node, **position;

	if (node == NULL) {
		if (bitree_size(tree) > 0)
			return -1;
		position = &tree->root;
	} else {
		if (bitree_left(node) != NULL)
			return -1;
		position = &node->right;
	}
	if ((new_node = (BiTreeNode *)malloc(sizeof(BiTreeNode))) == NULL)
		return -1;

	new_node->data = (void *)data;
	new_node->left = NULL;
	new_node->right = NULL;
	*position = new_node;

	tree->size++;

	return 0;
}

/**
 * 移除某个结点左边所有的结点
 * @param tree 树
 * @param node 指定的结点
 */
void bitree_rem_left(BiTree *tree, BiTreeNode *node)
{
	BiTreeNode **position;

	if (bitree_size(tree) == 0)
		return;

	if (node == NULL)
		position = &tree->root;
	else
		position = &node->left;

	if (*position != NULL) {
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);

		if (tree->destroy != NULL) {
			tree->destroy((*position)->data);
		}

		free(*position);
		*position = NULL;

		tree->size--;
	}
}

/**
 * 移除某个结点右边所有的结点
 * @param tree 树
 * @param node 指定的结点
 */
void bitree_rem_right(BiTree *tree, BiTreeNode *node)
{
	BiTreeNode **position;

	if (bitree_size(tree) == 0)
		return;

	if (node == NULL)
		position = &tree->root;
	else
		position = &node->right;

	if (*position != NULL) {
		bitree_rem_left(tree, *position);
		bitree_rem_right(tree, *position);

		if (tree->destroy != NULL) {
			tree->destroy((*position)->data);
		}

		free(*position);
		*position = NULL;

		tree->size--;
	}
}

/**
 * 合并两棵树
 * @param  merge 合并后的树
 * @param  left  合并前的左子树
 * @param  right 合并前的又子树
 * @param  data  新的树的跟结点的数据
 * @return       成功返回0，失败-1
 */
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data)
{
	bitree_init(merge, left->destroy);

	if (bitree_ins_left(merge, NULL, data) != 0) {
		bittree_destroy(merge);
		return -1;
	}

	bitree_root(merge)->left = bitree_root(left);
	bitree_root(merge)->right = bitree_root(right);
	// 调整树的大小
	merge->size = merge->size + bitree_size(left) + bitree_size(right);

	// 不允许原来的树访问合并后的结点
	left->root = NULL;
	left->size = 0;
	right->root = NULL;
	right->size = 0;

	return 0;
}