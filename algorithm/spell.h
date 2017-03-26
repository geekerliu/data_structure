// spell.h，使用二分查找实现拼写检查器
#ifndef SPELL_H
#define SPELL_H

#define SPELL_SIZE 31

int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word);

#endif