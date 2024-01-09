#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>

#define BUFFER_SIZE 20
#define DEFAULT_NUM 6

int compareData(void *arg1, void *arg2)
{
    int num1 = *(int *)arg1;
    int num2 = *(int *)arg2;

    return num1 == num2 ? 1 : 0;
}
int main()
{
    dynamicArray array;
    /* 初始化 */
    dynamicArrayInit(&array, BUFFER_SIZE);
    for (int idx = 1; idx <= DEFAULT_NUM; idx++)
    {
        dynamicArrayInsertData(&array, (void *)&idx);
    }
    
    /* 获取数组长度 */
    int size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);
    /* 获取数组容量 */
    int capacity = 0;
    dynamicArrayGetCapacity(&array, &capacity);
    printf("capacity:%d\n", capacity);
    /* 指定位置插入 */
    int val = 5;
    dynamicArrayAppointPosInsertData(&array, 5, (void *)&val);
      
    /* 获取数组长度 */
    size = 0;
    dynamicArrayGetSize(&array, &size);
    printf("size:%d\n", size);
    /* 获取数组容量 */
    capacity = 0;
    dynamicArrayGetCapacity(&array, &capacity);
    printf("capacity:%d\n", capacity);

    
    return 0;
}
