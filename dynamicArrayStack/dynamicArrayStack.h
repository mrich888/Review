#ifndef __DYNAMIC_ARRAY_STACK_H
#define __DYNAMIC_ARRAY_STACK_H

#include "common.h"

typedef dynamicArray dynamicArrayStack;

/* 栈的初始化 */
int dynamicArrayStackInit(dynamicArrayStack * pStack);

/* 压栈 */
int dynamicArrayStackPush(dynamicArrayStack * pStack, ELEMENTTYPE val);

/* 查看栈顶元素(双指针是为了可以输出结构体) */
int dynamicArrayStackTop(dynamicArrayStack * pStack, ELEMENTTYPE *pVal);

/* 出栈 */
int dynamicArrayStackPop(dynamicArrayStack * pStack);

/* 判断栈是否为空 */
int dynamicArrayStackIsEmpty(dynamicArrayStack * pStack);

/* 获取栈大小 */
int dynamicArrayStackGetSize(dynamicArrayStack * pStack, int * pSize);

/* 栈的销毁 */
int dynamicArrayStackDestroy(dynamicArrayStack * pStack);

#endif //__DYNAMIC_ARRAY_STACK_H