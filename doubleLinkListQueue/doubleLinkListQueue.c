#include <stdio.h>
#include "doubleLinkListQueue.h"
#include "doubleLinkList.h"

/* 状态码 */
typedef enum STATUS_CODE
{
    NOT_FIND ,
    ON_SUCCESS,
    NULL_PTR,
    MALLOC_ERROR,
    INVALID_ACCESS,
  
}STATUS_CODE;

/* 队列的初始化 */
int doubleLinkListQueueInit(doubleLinkListQueue ** pQueue)
{
    return doubleLinkListInit(pQueue);
}
/* 入队 */
int doubleLinkListQueueInsert(doubleLinkListQueue * pQueue, ELEMENTTYPE val)
{
    return doubleLinkListTailInsert(pQueue, val);
}
/* 队头元素 */
int doubleLinkListQueueTop(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal)
{
    return  doubleLinkListGetHeadVal(pQueue, (void **)&pVal);
}
/* 队尾元素 */
int doubleLinkListQueueTail(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal)
{
    return  doubleLinkListGetTailVal(pQueue, (void **)&pVal);
}
/* 出队 */
int doubleLinkListQueuePop(doubleLinkListQueue * pQueue)
{
    return doubleLinkListDelete(pQueue);
}
/* 获取队列的长度 */
int doubleLinkListQueueGeiSize(doubleLinkListQueue * pQueue, int *pSize)
{
    if (pQueue == NULL)
    {
        return NULL_PTR;
    }
    if (pSize)
    {
        *pSize = pQueue->len;
    }
    return pQueue->len;  
}
/* 获取队列是否为空 */
int doubleLinkListQueueIsEmpty(doubleLinkListQueue * pQueue)
{  
    if (pQueue->len == 0)
    {
        return 0;
    }
    return ON_SUCCESS;
}
/* 队列的销毁 */
int doubleLinkListQueueDestroy(doubleLinkListQueue * pQueue)
{
    return doubleLinkListDelete(pQueue);
}
