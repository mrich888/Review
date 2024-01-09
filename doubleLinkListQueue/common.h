#ifndef __COMMON_H
#define __COMMON_H

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

#endif //__COMMON_H