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
    NOT_FIND,
}STATUS_CODE;
static doubleLinkNode * createDoubleLinkNode(ELEMENTTYPE val);
static int findAppointPos(doubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int * pPos);

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
doubleLinkListDelete(doubleLinkList * pList)
{
    return doubleLinkListDeleteAppointPosVal(pList, pList->len);
}
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
    /* ⭐如果不将需要删除的结点拿出来的话你后面没办法释放 */
    /* ⭐如果是删除尾巴，需要先将尾指针移动到前一个并保存下来，不然将尾结点删除之后就找不到尾指针了 */
    doubleLinkNode * travelNode = pList->head;//从头结点开始遍历 
    doubleLinkNode * delNode = NULL;
    int *tempNode = NULL;
    int flag = 0;//打标志
    if (pos == pList->len)
    {
        tempNode = pList->tail;//保存原尾指针
        pList->tail = pList->tail->prev;//将尾指针向前移动
        delNode = tempNode;//删除结点是原尾结点
        travelNode->prev->next = travelNode->next;//NULL
        flag = 1;
    }
    else
    {
        while (pos)
        {
            pos--;
            travelNode = travelNode->next;   
        }
        delNode = travelNode->next;
        delNode->next->prev = travelNode;
        travelNode->next = delNode->next;
    }
    /* 删除一个结点，需要将结点释放 */
    if (delNode != NULL)
    {
        free(delNode);
        delNode = NULL;
    }
    /* 链表长度-- */
    (pList->len)--;
    return ret;
}

/* 通过值找到指定位置 */
static int findAppointPos(doubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2), int * pPos)
{
    /* 通过值找到指定位置，将位置传出去 */
    /* 遍历结束条件是全部，返回条件分找到了和没找到 */
    int cmp = 0; // comFunc val1 == val2 ? 1 : 0; 相等返回1
    doubleLinkNode * travelNode = pList->head->next;//从首元结点开始遍历
    int pos = 0;
    while (travelNode != NULL)
    {
        pos++;
        cmp = compareFunc(val, travelNode->data);
        if (cmp == 1)
        {
            /* ⭐解引用 */
            *pPos = pos;
            return pos;
        }
        #if 0
        /* 不需要特意在返回 */
        else
        {
            return NOT_FIND;
        }
        #endif
        travelNode = travelNode->next;
    }
    *pPos = NOT_FIND;
    return NOT_FIND;
}
/* 链表删除指定值 */
doubleLinkListDeleteAppointVal(doubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2))
{
    int ret = 0;
    /* 首先要将传入的值与链表中的值作比较，有两种情况：存在和不存在（这也是循环依据） */
    /* 存在的话根据值找到指定位置--静态函数 */
    int pos = 0;
    pos = findAppointPos(pList, (void *)&val, compareFunc, pos);
    return doubleLinkListDeleteAppointPosVal(pList, pos);
    return ret;
}
/* 链表的长度 */
doubleLinkListGetLength(doubleLinkList * pList, int *pSize)
{
    /* 判空 */
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    if (pSize)
    {
        *pSize = pList->len;
    }
    return pList->len;
}
/* 链表的遍历 */
doubleLinkListForeach(doubleLinkList * pList, int (* printFunc)(ELEMENTTYPE val))
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    /* 遍历指针:从首元结点开始遍历 */
    doubleLinkNode * travelNode = pList->head->next;
    while (travelNode != NULL)
    {
        /* 就需要输出：输出格式自定义 */
        printFunc((void *)travelNode->data);
        travelNode = travelNode->next;
    }
    return ret;
}
/* 链表的逆序 */
doubleLinkListBackForeach(doubleLinkList * pList)
{
    int ret = 0;
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    /* 遍历指针:从尾结点开始遍历 */
    doubleLinkNode * travelNode = pList->tail;
    while (travelNode != pList->head)
    {
        /* 就需要输出：输出格式自定义 */
        printFunc((void *)travelNode->data);
        travelNode = travelNode->prev;
    }
    return ret;
}
/* 链表的销毁 */
doubleLinkListDestroy(doubleLinkList * pList)
{
    /* 可以复用尾删 */
    return doubleLinkListDelete(pList);
}
/* 获取链表 头位置值 */
int doubleLinkListGetHeadVal(doubleLinkList * pList, ELEMENTTYPE *val)
{
    if (pList == NULL)
    {
        return NULL_PTR;
    }
    if (val)
    {
        *val = pList->head->next->data;
    }
    return pList->head->next->data;
}
/* 获取链表 尾位置值 */
int doubleLinkListGetTailVal(doubleLinkList * pList, ELEMENTTYPE *val)
{
      if (pList == NULL)
    {
        return NULL_PTR;
    }
    if (val)
    {
        *val = pList->tail->data;
    }
    return pList->tail->data;
}