#ifndef __DOUBLE_LINKLIST_H
#define __DOUBLE_LINKLIST_H

#define ELEMENTTYPE void *

/* 双链表中需要维护两个结构体：①链表 ②结点 */

/* ①链表：长度，头尾指针 */
typedef struct doubleLinkList
{
    int len;
    doubleLinkNode *head;
    doubleLinkNode *tail;  
}doubleLinkList;

/* ②结点：数据；前后指针 */
typedef struct doubleLinkNode
{
    ELEMENTTYPE data; //不知道数据是什么类型
    struct doubleLinkNode *prev;
    struct doubleLinkNode *next;
}doubleLinkNode;

/* API 接口 */
/* 链表的初始化 */
doubleLinkListInit(doubleLinkList ** pList);
/* 链表的头插 */
doubleLinkListHeadInsert(doubleLinkList * pList, ELEMENTTYPE val);
/* 链表的尾插 */
doubleLinkListTailInsert(doubleLinkList * pList, ELEMENTTYPE val);
/* 链表的指定位置插 */
doubleLinkListAppointPosInsert(doubleLinkList * pList, int pos, ELEMENTTYPE val);
/* 链表的尾删 */
doubleLinkListDelete(doubleLinkList * pList);
/* 链表的指定位置删 */
doubleLinkListDeleteAppointPosVal(doubleLinkList * pList, int pos);
/* 链表删除指定值 */
doubleLinkListDeleteAppointVal(doubleLinkList * pList, ELEMENTTYPE val, int (*compareFunc)(ELEMENTTYPE val1, ELEMENTTYPE val2));
/* 链表的长度 */
doubleLinkListGetLength(doubleLinkList * pList, int *pSize);
/* 链表的遍历 */
doubleLinkListForeach(doubleLinkList * pList, int (* printFunc)(ELEMENTTYPE val));
/* 链表的逆序 */
doubleLinkListBackForeach(doubleLinkList * pList);
/* 链表的销毁 */
doubleLinkListDestroy(doubleLinkList * pList);
/* 获取链表 头位置值 */
int doubleLinkListGetHeadVal(doubleLinkList * pList, ELEMENTTYPE *val);
/* 获取链表 尾位置值 */
int doubleLinkListGetTailVal(doubleLinkList * pList, ELEMENTTYPE *val);
/* 获取链表 指定位置值 */
int doubleLinkListGetAppointPosVal(doubleLinkList * pList, int pos, ELEMENTTYPE *val);
#endif //__DOUBLE_LINKLIST_H