#include <stdio.h>
#include "dynamicArray.h"
#include <string.h>
#include <stdlib.h>

typedef enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
}STATUS_CODE;

#define DEFAULT_SIZE 10
/* 静态前置 */
static int expandDynamicCapacity(dynamicArray *pArray);

/* 初始化 */
int dynamicArrayInit(dynamicArray * pArray, int capacity)
{
    /* 判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 避免参数中传入非法值 */
    if (capacity < 0)
    {
        capacity = DEFAULT_SIZE;
    }
    /* 指针类型必须分配空间 */
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * capacity);
    if (pArray->data == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清楚脏数据 */
    memset(pArray->data, 0, sizeof(ELEMENTTYPE) * capacity);
    /* 其他属性初始化 */
    pArray->len = 0;
    pArray->capacity = capacity;
    
    return ON_SUCCESS;
}

/* 插入 默认尾插入*/
int dynamicArrayInsertData(dynamicArray * pArray, ELEMENTTYPE val)
{
    return dynamicArrayAppointPosInsertData(pArray, pArray->len, val);
}

/* 扩容 */
static int expandDynamicCapacity(dynamicArray *pArray)
{
    int ret = 0;
    /* 扩容至1.5倍,扩的是容量 */
    int needExpandCapacity = pArray->capacity + ((pArray->capacity) >> 1);
    /* 先将原来的数组进行备份,备份指针的类型为万能指针 */
    ELEMENTTYPE * cpyPtr = pArray->data;
    /* 对扩容后的数组分配空间 */
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * pArray->capacity);
    if (pArray == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 将原来的复制至新的数组里面,数组长度为len */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = cpyPtr[idx];
    }
    /* 释放原来的,它本来是是空的，若不是空的则释放 */
    if (cpyPtr != NULL)
    {
        free(cpyPtr);
        cpyPtr = NULL;
    }
    /* 更新数组容量 */
    pArray->capacity = needExpandCapacity;
    return ret;
}
/* 指定位置插入 */
int dynamicArrayAppointPosInsertData(dynamicArray * pArray, int pos, ELEMENTTYPE val)
{
    /* 先判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 判断位置是否合法 */
    if (pos < 0 || pos > pArray->capacity)
    {
        return INVALID_ACCESS;
    }
    /* 插入之前得先判断是否扩容 -- 静态函数 */
    /* 假设再插入现有长度一半的话则扩容 */
    if ((pArray->len + pArray->len >> 1) >= pArray->capacity)
    {
        expandDynamicCapacity(pArray);
    }
    /* 扩容之后数据后移 */  
    for (int idx = pArray->len; idx > pos; idx--)
    {
        pArray->data[idx] = pArray->data[idx - 1];
    }
    /* 插入目标值 */
    pArray->data[pos] = val;
    /* 数组长度增加 */
    pArray->len++;

    return ON_SUCCESS;
}

/* 修改指定位置的数据 */
int dynamicArrayModifyAppointPosData(dynamicArray * pArray, int pos, ELEMENTTYPE val)
{
    int ret = 0;
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 判断位置是否合法 */
    if (pos < 0 || pos > pArray->capacity)
    {
        return INVALID_ACCESS;
    }
    /* 更新数据 */
    pArray->data[pos]= val;
    return ret;
}

/* 删除数据，默认尾删除 */
int dynamicArrayDeleteData(dynamicArray * pArray)
{
    return dynamicArrayDeleteAppointPosData(pArray, pArray->len - 1);   
}

/* 缩容 */
int shrinkDynamicCapacity(dynamicArray *pArray)
{
    int ret = 0;
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 所容后的容量 */
    int needshrinkCapacity = pArray->capacity - (pArray->capacity >> 1);
    /* 复制原来的数组 */
    ELEMENTTYPE * copyPtr = pArray->data;
    /* 给所容后的数组分配空间 */
    pArray->data = (ELEMENTTYPE *)malloc(sizeof(ELEMENTTYPE) * pArray->capacity);
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 将原来的数据复制到缩容后的数组中 */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        pArray->data[idx] = copyPtr[idx];
    }
    /* 释放原来的数组 */
    if (copyPtr != NULL)
    {
        free(copyPtr);
        copyPtr= NULL;
    }
    /* 更新数组长度 */
    pArray->capacity = needshrinkCapacity;

    return ret;
}

/* 指定位置删除*/
int dynamicArrayDeleteAppointPosData(dynamicArray * pArray, int pos)
{
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 判断位置是否合法 */
    if (pos < 0 || pos > pArray->capacity)
    {
        return INVALID_ACCESS;
    }
    /* 删除：后一个直接覆盖 */
    for (int idx = pos; idx < pArray->len; idx++)
    {
        pArray->data[idx] = pArray->data[idx + 1];
    }
    /* 删除之后判断数组是否需要缩容 */
    if ((pArray->len + (pArray->len >> 1) > pArray->capacity) )
    {
        shrinkDynamicCapacity(pArray);
    }
    /* 更新数组容量 */
    (pArray->len)--;
    return ON_SUCCESS;
}

static int compareFunc(ELEMENTTYPE val1, ELEMENTTYPE val2)
{

}

/* 指定元素删除 */
int dynamicArrayDeleteAppointData(dynamicArray * pArray,  ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2))
{
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 首先需要判断要删除的元素再数组中是否存在：需要遍历的同时去寻找，确定这个元素的位置，复用删除指定位置  */
    for (int idx = 0; idx < pArray->len; idx++)
    {
        /* 1是成功 */
        if (compareFunc(val, pArray->data[idx]) == 1)
        {
            dynamicArrayDeleteAppointPosData(pArray, idx);
        }
        
    }
    return ON_SUCCESS;
}

/* 动态数组的销毁 */
int dynamicArrayDestroy(dynamicArray * pArray)
{
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    if (pArray->data != NULL)
    {
        free(pArray->data);
        pArray->data = NULL;
    }
    return ON_SUCCESS;
}

/* 获取数组的大小 */
int dynamicArrayGetSize(dynamicArray *pArray, int *pSize)
{
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 如果pSize有效，就用它承接数组长度*/
    if (pSize != NULL)
    {
        *pSize = pArray->len;
    }
    
    return pArray->len;
}

/* 获取数组的容量 */
int dynamicArrayGetCapacity(dynamicArray *pArray, int *pCapacity)
{
    /* 数组判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    if (pCapacity != NULL)
    {
        *pCapacity = pArray->capacity;
    }
    
    return pArray->capacity;
}

/* 获取指定位置的元素数据 */
int dynamicArrayGetAppointPosVal(dynamicArray *pArray, int pos, ELEMENTTYPE *pVal)
{
    /* 先判空 */
    if (pArray == NULL)
    {
        return NULL_PTR;
    }
    /* 判断位置是否合法 */
    if (pos < 0 || pos > pArray->capacity)
    {
        return INVALID_ACCESS;
    }
    if (pVal != NULL)
    {
        *pVal = pArray->data[pos];
    }
    return ON_SUCCESS;
}