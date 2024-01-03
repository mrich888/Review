#include <stdio.h>
#include <string.h>
#include "dynamicArrayStack.h"
#include "common.h"

/* 状态码 */
enum STATUS_CODE
{
    ILVALID,
    ON_SUCCESS,
};
#define BUFFER_SIZE 20

int stringIsValid(char *ptr)
{
    /* 判断字符串中括号数量是否对即左括号是否等于右括号的数量 */
    /* ①将字符串中的左括号入栈 */
    /* ②遇到右括号与左括号一起输出 */
    /* ③除了不匹配的情况下其他都匹配：
       ·当右括号出现的时候左括号还没入栈（即栈里是空的）
       ·当遍历到（ 的时候，栈顶元素不是它（另外两个同理）
       ·都遍历完了栈里还有东西它也是非法的
    */
    /* 之前想到的是：将左括号都入栈，左括号结束后才是右括号，然后去判断出现的右括号是否与栈顶元素比较，但这里出现的误区是：
        ·万一第一个就是右括号的话，根本不入栈，也就不能比较，其实在这里就该返回无效字符串了
        ·进入到第else里面的时候就证明遇到右括号，就应该开始匹配，但只考虑到了成功的情况，忽略不成功了的话就应该也返回无效
        ·也忽略了之前都匹配但是又出现了多出了一个右括号
        ·把左括号和右括号出现的情况想象的太理想化了
        ·遍历出现的括号顺序并不是左完了才右，有可能是左入栈后就出现了右，然后再接着左
        ·【优化】比起用pos，指针移动更方便，截止条件就是 '\0'
    */
    char *array = ptr;
    /* 使用栈 */
    dynamicArrayStack stack;
    dynamicArrayStackInit(&stack);

    char *topVal = NULL;
    /* 其他就需要先将所有左括号入栈 */
    while (*array != '\0')
    {
        if (*array == '(' || *array == '{' ||  *array == '[')
        {
            /* 入栈 */
            dynamicArrayStackPush(&stack, (void *)array);
        }
        else
        {
            /* ①程序运行到这里证明出现了右括号，但此时若栈里没有左元素则是无效的 */
            if (dynamicArrayStackIsEmpty(&stack))
            {
                return ILVALID;
            }
            /* ②遇到右括号的话就开始匹配，考虑不匹配的三种情况 */
            /* 查看栈顶元素 */
            /* 二级指针 */
            dynamicArrayStackTop(&stack, (void *)&topVal);
            dynamicArrayStackPop(&stack);
            if (*array == ')' && *topVal != '(')
            {
                return ILVALID;
            }
            else if (*array == '}' && *topVal != '{')
            {
                return ILVALID;
            }
            else if (*array == ']' && *topVal != '[')
            {
                return ILVALID;                
            } 
        }
        array++;
    }
    /* 程序运行到这里证明字符串已经遍历结束 */
    /* 成功的条件只有一个：匹配结束后栈里没有元素了，否则都是无效的 */
    if (dynamicArrayStackIsEmpty(&stack))
    {
        dynamicArrayStackDestroy(&stack);
        return ON_SUCCESS;
    }
    /* 释放栈 */
    dynamicArrayStackDestroy(&stack);
    return ILVALID;   
}


int main()
{
    int ret = 0;
    /* 定义一个字符数组 */
    char array[BUFFER_SIZE] = "{()())}";
    ret = stringIsValid(array);
    printf("ret:%d\n", ret);
    return ret;
}