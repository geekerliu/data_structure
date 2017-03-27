// cover.c
#include <stdlib.h>
#include "cover.h"

/**
 * 集合覆盖问题的实现。
 * @param  members  待覆盖的集合
 * @param  subsets  用来覆盖的子集
 * @param  covering 用来保存覆盖集
 * @return          成功返回0；不可能完全覆盖返回1；其它返回-1
 */
int cover(Set *members, Set *subsets, Set *covering)
{
	Set intersection;
	KSet *subset;
	ListElmt *member, *max_member;
	void *data;
	int max_size;

	set_init(covering, subsets->match, NULL);

	while (set_size(members) > 0 && set_size(subsets) > 0) {
		max_size = 0;
		// 寻找一个拥有最大交集的子集
		for (member = list_head(subsets); member != NULL;
		     member = list_next(member)) {
			if (set_intersection(&intersection,
			                     &((KSet *)list_data(member))->set, members) != 0) {
				return -1;
			}

			if (set_size(&intersection) > max_size) {
				max_member = member;
				max_size = set_size(&intersection);
			}
			// 清空这个集合
			set_destroy(&intersection);
		}

		// 没有找到交集
		if (max_size == 0)
			return 1;

		// 把找到的子集放在结果的集合中
		subset = (KSet *)list_data(max_member);
		if (set_insert(covering, subset) != 0)
			return -1;

		// 将选中的子集中的元素从members中移除
		for (member = list_head(&((KSet *)list_data(max_member))->set);
		     member != NULL; member = list_next(member)) {
			data = list_data(member);
			if (set_remove(members, (void**)&data) == 0 && members->destroy)
				members->destroy(data);
		}

		// 将选中的子集从集合中移除
		if (set_remove(subsets, (void**)&subset) != 0)
			return -1;
	}

	// 如果待覆盖的集合中还有元素，则表示不能完全覆盖
	if (set_size(members) > 0)
		return -1;

	return 0;
}