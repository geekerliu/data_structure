// directls.h,快速排序的例子，目录列表
#ifndef DIRECTLS_H
#define DIRECTLS_H

#include <dirent.h>

typedef struct Directory_ {
	char name[MAXNAMELEN + 1];
} Directory;

int directory(const char *path, Directory **dir);

#endif