#ifndef __DOUBLELINKLIST_QUEUE_H_
#define __DOUBLELINKLIST_QUEUE_H_

#include "common.h"
/* 在链表的基础上实现队列 */

/* 重命名 */
typedef doubleLinkList doubleLinkListQueue;

/* 队列的初始化 */
int doubleLinkListQueueInit(doubleLinkListQueue ** pQueue);
/* 入队 */
int doubleLinkListQueueInsert(doubleLinkListQueue * pQueue, ELEMENTTYPE val);
/* 队头元素 */
int doubleLinkListQueueTop(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal);
/* 队尾元素 */
int doubleLinkListQueueTail(doubleLinkListQueue * pQueue, ELEMENTTYPE * pVal);
/* 出队 */
int doubleLinkListQueuePop(doubleLinkListQueue * pQueue);
/* 获取队列的长度 */
int doubleLinkListQueueGeiSize(doubleLinkListQueue * pQueue, int *pSize);
/* 获取队列是否为空 */
int doubleLinkListQueueIsEmpty(doubleLinkListQueue * pQueue);
/* 队列的销毁 */
int doubleLinkListQueueDestroy(doubleLinkListQueue * pQueue);

#endif //__DOUBLELINKLIST_QUEUE_H_