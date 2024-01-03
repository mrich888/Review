#include "dynamicArrayStack.h"
#include "dynamicArray.h"

#define DEFAULT_NUM 10
/* 栈的初始化 */
int dynamicArrayStackInit(dynamicArrayStack * pStack)
{
    return dynamicArrayInit(pStack, DEFAULT_NUM);
}

/* 压栈 */
int dynamicArrayStackPush(dynamicArrayStack * pStack, ELEMENTTYPE val)
{
    /* 压栈到栈底，尾插 */
    return dynamicArrayInsertData(pStack, val);
}

/* 查看栈顶元素(双指针是为了可以输出结构体) */
int dynamicArrayStackTop(dynamicArrayStack * pStack, ELEMENTTYPE *pVal)
{
    return dynamicArrayGetAppointPosVal(pStack, pStack->len - 1, pVal);
}

/* 出栈 */
int dynamicArrayStackPop(dynamicArrayStack * pStack)
{
    dynamicArrayDeleteData(pStack);
}

/* 判断栈是否为空 1 ：0 */
int dynamicArrayStackIsEmpty(dynamicArrayStack * pStack)
{
    int size = 0;
    /* 获取数组大小 */
    dynamicArrayGetSize(pStack, &size);
    return size == 0 ? 1 : 0;
}

/* 获取栈大小 */
int dynamicArrayStackGetSize(dynamicArrayStack * pStack, int * pSize)
{
    return dynamicArrayGetSize(pStack, pSize);
}

/* 栈的销毁 */
int dynamicArrayStackDestroy(dynamicArrayStack * pStack)
{
    return dynamicArrayDeleteData(pStack);
}
