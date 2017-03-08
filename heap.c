//heap.c，最大值堆
#include <stdlib.h>
#include <string.h>

#include "heap.h"

#define heap_parent(npos) ((int)(((npos) - 1) / 2))
#define heap_left(npos) (((npos) * 2) +1)
#define heap_right(npos) (((npos) * 2) + 2)

void heap_init(Heap *heap, int (*compare)(const void *key1, const void *key2),
               void (*destroy)(void *data))
{
	heap->size = 0;
	heap->compare = compare;
	heap->destroy = destroy;
	heap->tree = NULL;
}

void heap_destroy(Heap *heap)
{
	int i;
	if (heap->destroy != NULL) {
		for (i = 0; i < heap_size(heap); i++) {
			heap->destroy(heap->tree[i]);
		}
	}

	free(heap->tree);

	memset(heap, 0, sizeof(Heap));
}

int heap_insert(Heap *heap, const void *data)
{
	void *temp;
	int ipos, ppos;

	if ((temp = (void **)realloc(heap->tree,
	                             (heap_size(heap) + 1) * sizeof(void *))) == NULL) {
		return -1;
	} else {
		heap->tree = temp;
	}

	// 将结点插入到末尾
	heap->tree[heap_size(heap)] = (void *)data;
	ipos = heap_size(heap);
	ppos = heap_parent(ipos);

	// 调整数据
	while (ipos > 0 && heap->compare(heap->tree[ppos], heap->tree[ipos]) < 0) {
		temp = heap->tree[ppos];
		heap->tree[ppos] = heap->tree[ipos];
		heap->tree[ipos] = temp;

		ipos = ppos;
		ppos = heap_parent(ipos);
	}

	heap->size++;

	return 0;
}

/**
 * 从堆heap中释放堆顶部的结点。返回时，data指向被释放结点中存储的数据。
 * 与data相关的内存将有函数的调用者来管理。
 * @param  heap [description]
 * @param  data [description]
 * @return      [description]
 */
int heap_extract(Heap *heap, void **data)
{
	void *save, *temp;
	int ipos, lpos, rpos, mpos;

	if (heap_size(heap) == 0) {
		return -1;
	}
	*data = heap->tree[0];
	save = heap->tree[heap_size(heap) - 1];

	if (heap_size(heap) - 1 > 0) {
		if ((temp = (void **)realloc(heap->tree,
		                             (heap_size(heap) - 1) * sizeof(void *))) == NULL) {
			return -1;
		} else {
			heap->tree = temp;
		}
		heap->size--;
	} else {
		free(heap->tree);
		heap->tree = NULL;
		heap->size = 0;
		return 0;
	}

	// 把最后一个结点放到顶点
	heap->tree[0] = save;
	ipos = 0;
	lpos = heap_left(ipos);
	rpos = heap_right(ipos);

	while (1) {
		lpos = heap_left(ipos);
		rpos = heap_right(ipos);
		// 如果左边结点比右边结点大
		if (lpos < heap_size(heap) && heap->compare(heap->tree[lpos],
		        heap->tree[ipos]) > 0) {
			mpos = lpos;
		} else {
			mpos = ipos;
		}

		if (rpos < heap_size(heap) && heap->compare(heap->tree[rpos],
		        heap->tree[mpos]) > 0) {
			mpos = rpos;
		}

		if (mpos == ipos) {
			break;
		} else {
			temp = heap->tree[mpos];
			heap->tree[mpos] = heap->tree[ipos];
			heap->tree[ipos] = temp;
			// 继续遍历下面一层
			ipos = mpos;
		}
	}
	return 0;
}


