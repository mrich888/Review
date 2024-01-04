#include "doubleLinkList.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 状态码 */
typedef enum STATUS_CODE
{
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
}STATUS_CODE;

static doubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val)
{
    /* 给结点分配空间 */
    doubleLinkNode * newNode =(doubleLinkNode *)malloc(sizeof(doubleLinkNode) * 1);
    /* 判断是否分配成功 */
    if (newNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清楚脏数据 */
    memset(newNode, 0, sizeof(doubleLinkNode) * 1);
    /* 结点初始化 */
    newNode->data = 0;
    newNode->prev = NULL;
    newNode->next =NULL;
    /* ⭐既然是新结点，就是为了赋值使用的，怎么能忘记赋值呢 */
    newNode->data = val;
    /* ⭐新结点需要作为返回值 */
    return newNode;
}

/* 链表的初始化 */
doubleLinkListInit(doubleLinkList ** pList)
{
    int ret= 0;
    /* 指针需要分配空间 */
    doubleLinkList * list = (doubleLinkList *)malloc(sizeof(doubleLinkList) * 1);
    /* 判断是否分配成功 */
    if (list == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清空脏数据 */
    memset(list, 0, sizeof(doubleLinkList) * 1);
    /* 给结点分配空间 */
    doubleLinkNode * linkNode =(doubleLinkNode *)malloc(sizeof(doubleLinkNode) * 1);
    /* 判断是否分配成功 */
    if (linkNode == NULL)
    {
        return MALLOC_ERROR;
    }
    /* 清楚脏数据 */
    memset(linkNode, 0, sizeof(doubleLinkNode) * 1);
    /* 链表初始化 */
    list->len = 0;
    list->head = list->tail;//初始化头尾指针在同一个位置
    /* 结点初始化 */
    list->head->data = 0;
    list->head->prev = NULL;
    list->head->next =NULL;
    /* 参数传的是一个二级指针，所以开头就需要分配空间而不是直接判空 */
    *pList = list;
    return ret;
}
/* 链表的头插 */
doubleLinkListHeadInsert(doubleLinkList * pList, ELEMENTTYPE val)
{
    return(doubleLinkListAppointPosInsert(pList, 0, val));
}
/* 链表的尾插 */
doubleLinkListTailInsert(doubleLinkList * pList, ELEMENTTYPE val)
{
    return(doubleLinkListAppointPosInsert(pList, pList->len, val));
}
/* 链表的指定位置插 */
doubleLinkListAppointPosInsert(doubleLinkList * pList, int pos, ELEMENTTYPE val)
{
    /*⭐ 忘记考虑尾指针需要变动了 */
    int ret = 0;
    /* 一级指针传的是地址，所以先判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    /* 要想插入，首先判断位置合不合法 */
    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
    /* 插入的应该是结点，所以需要先将值封装成结点 */
    doubleLinkNode * newNode = createDoubleLinkNode(val);
    doubleLinkNode * travelNode = pList->head;//从头结点开始遍历 
    /* 合法的话开始找位置，它存在直接插在链表尾部，此时需要变动尾指针 */
    /* ⭐插入其他位置和插入尾巴是互斥情况，把while放在else里面，就可以实现合并代码了 */
    int flag = 0;//打标志
    if (pos == pList->len)
    {
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while (pos)
        {
            pos--;
            travelNode = travelNode->next;   
        }
        travelNode->next->prev = newNode;
    }
    /* 此时遍历指针指向的就是要插入结点的前一个位置，插在当前后面就是想要插入的位置，插入需要注意指针的断和连 */
    newNode->next = travelNode->next;
    travelNode->next = newNode;
    newNode->prev = travelNode;
    /* 此时需要变动尾指针 */
    if (flag == 1)
    {
        pList->tail = newNode;
    }
    /* 插入之后需要更新链表长度 */
    (pList->len)++;
    return ret;
}
/* 链表的尾删 */
doubleLinkListDelete(doubleLinkList * pList);
/* 链表的指定位置删 */
doubleLinkListDeleteAppointPosVal(doubleLinkList * pList, int pos)
{
    int ret = 0;
    /* 判空 */
    if (pList == NULL)
    {
       return NULL_PTR;
    }
    /* 要想删除，首先判断位置合不合法 */
    if (pos < 0 || pos > pList->len)
    {
        return INVALID_ACCESS;
    }
    /* 删除的位置有两种情况：尾位置和其他位置， 所以也需要考虑尾指针的变动 */
    doubleLinkNode * travelNode = pList->head;//从头结点开始遍历 
    int flag = 0;//打标志
    if (pos == pList->len)
    {
        travelNode = pList->tail;
        flag = 1;
    }
    else
    {
        while (pos)
        {
            pos--;
            travelNode = travelNode->next;   
        }
        travelNode->next->next->prev = travelNode;
    }
    /* 指针的断和连 */
    travelNode->next = travelNode->next->next;
    /* 尾指针变动 */
    if (flag == 1)
    {
        pList->tail = travelNode;
    }
    /* 删除一个结点，需要将结点释放 */
    
    
    return ret;
}
/* 链表删除指定值 */
doubleLinkListDeleteAppointVal(doubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2))
{


}
/* 链表的遍历 */
doubleLinkListForeach(doubleLinkList * pList);
/* 链表的逆序 */
doubleLinkListBackForeach(doubleLinkList * pList);
/* 链表的销毁 */
doubleLinkListDestroy(doubleLinkList * pList);