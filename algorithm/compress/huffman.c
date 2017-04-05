// huffman.c
#include <limits.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>

#include "bit.h"
#include "compress.h"
#include "../../data_structure/pqueue.h"

static int compare_freq(const void *tree1, const void *tree2)
{
	HuffNode *root1, *root2;

	root1 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree1));
	root2 = (HuffNode *)bitree_data(bitree_root((const BiTree *)tree2));

	if (root1->freq < root2->freq)
		return 1;
	else if (root1->freq > root2->freq)
		return -1;
	else
		return 0;
}

static void destroy_tree(void *tree)
{
	bittree_destroy(tree);
	free(tree);
}

static int build_tree(int *freqs, BiTree **tree)
{
	BiTree *init, *merge, *left, *right;
	PQueue pqueue;
	HuffNode *data;
	int size, c;

	*tree = NULL;

	for (c = 0; c <= UCHAR_MAX; c++) {
		
	}
}