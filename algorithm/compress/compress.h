// compress.h，数据压缩头文件
#ifndef COMPRESS_H
#define COMPRESS_H

#include "../../data_structure/bitree.h"


typedef struct HuffNode_ {
	unsigned char symbol;
	int freq;
} HuffNode;

typedef struct HuffCode_ {
	unsigned char      used;
	unsigned short     code;
	unsigned char      size;
} HuffCode;

#define LZ77_TYPE_BITS 1
#define LZ77_WINOFF_BITS 12
#define LZ77_BUFLEN_BITS 5
#define LZ77_NEXT_BITS 8

#define LZ77_WINDOW_SIZE 4096
#define LZ77_BUFFER_SIZE 32

#define LZ77_PHRASE_BITS (LZ77_TYPE_BITS+LZ77_WINOFF_BITS\
                                         +LZ77_NEXT_BITS+LZ77_BUFLEN_BITS)
#define LZ77_SYMBOL_BITS (LZ77_TYPE_BITS+LZ77_NEXT_BITS)


/**
 * 霍夫曼压缩
 * @param  original   原始数据
 * @param  compressed 用于存放压缩后的数据
 * @param  size       原始数据的大小
 * @return            成功，返回压缩后数据的字节数；否则，返回-1
 */
int huffman_compress(const unsigned char *original, unsigned char
                     **compressed, int size);

/**
 * 霍夫曼解压缩
 * @param  compressed 压缩后的数据
 * @param  original   解压后的原始数据
 * @return            成功：返回恢复后数据的字节数；失败：-1
 */
int huffman_uncompress(const unsigned char *compressed, unsigned char
                       **original);

int lz77_compress(const unsigned char *original, unsigned char **compressed,
                  int size);

int lz77_uncompress(const unsigned char *compressed, unsigned char
                    **original);

#endif
