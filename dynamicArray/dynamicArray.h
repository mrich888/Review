#ifndef __DYNAMIC_ARRAY_H_
#define __DYNAMIC_ARRAY_H_

#define ELEMENTTYPE void *

typedef struct dynamicArray
{
    ELEMENTTYPE *data; //空间
    int len; //长度
    int capacity; //容量
}dynamicArray;

/* 初始化 */
int dynamicArrayInit(dynamicArray * pArray, int capacity);

/* 插入 默认尾插入*/
int dynamicArrayInsertData(dynamicArray * pArray, ELEMENTTYPE val);

/* 指定位置插入 */
int dynamicArrayAppointPosInsertData(dynamicArray * pArray, int pos, ELEMENTTYPE val);

/* 修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray * pArray, int pos, ELEMENTTYPE val);

/* 删除数据，默认尾删除 */
int dynamicArrayDeleteData(dynamicArray * pArray);

/* 指定位置删除*/
int dynamicArrayDeleteAppointPosData(dynamicArray * pArray, int pos);

/* 指定元素删除 */
int dynamicArrayDeleteAppointData(dynamicArray * pArray,  ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2));

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray);

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize);

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity);

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal);

#endif //__DYNAMIC_ARRAY_H_