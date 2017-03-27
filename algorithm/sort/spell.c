// spell.c
#include <string.h>

#include "bisearch.h"
#include "spell.h"

static int compare_str(const void *str1, const void *str2)
{
	int retval;

	if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0)
		return 1;
	else if (retval < 0)
		return -1;
	else
		return 0;
}

// int main(int argc, char const *argv[])
// {
// 	char a[2][3] = {{'1','2','3'},{'4','5','6'}};
// 	char (*p)[3] = a;
// 	char b[2][32] = {"hello", "word"};
// 	char (*p1)[32] = b;
// 	int i, j;

// 	for (i = 0; i < 2; i++)
// 		for (j = 0; j < 3; j++)
// 			printf("%c\n", p[i][j]);


// 	for (i = 0; i < 2; i++)
// 		printf("%s\n", p1[i]);

// 	return 0;
// }

/**
 * dictionary:指向一维数组类型的指针，每个一维数组大小为SPELL_SIZE
 * size:dictionary中单词个数
 * word:要搜索的单词
 */
int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word)
{
	if (bisearch(dictionary, word, size, SPELL_SIZE, compare_str) >= 0)
		return 1;
	else
		return 0;
}