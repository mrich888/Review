#ifndef __COMMON_H
#define __COMMON_H

#define ELEMENTTYPE void *

typedef struct dynamicArray
{
    ELEMENTTYPE *data; //空间
    int len; //长度
    int capacity; //容量
}dynamicArray;

#endif//__COMMON_H
