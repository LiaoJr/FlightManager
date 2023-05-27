
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


#ifndef LIST_H

#define LIST_H

/*定义航班信息结构体模板*/
typedef struct info{
	char price[8];      //价格
	char FilghtNum[8];  //航班号
	char time[64];  //起飞时间
	char start[64]; //出发地
	char dest[64];  //目的地
	char board[4];  //登机口
	
}Info_t;

/*结点结构体模板*/
typedef struct node{
    Info_t Info;
    struct node *next;
}Node_t;

/*定义头结点（管理结构体）模板*/
typedef struct HeadNode{
    int NodeNum;
    Node_t *Head;
    Node_t *Tail;
}ManNode_t;



/*----------------------函数声明----------------------*/
/*链表创建*/
ManNode_t * LinkedList_Create(void);

/*链表结点创建*/
Node_t * LinkedList_NewNode(Info_t *fInfo);

/*判断函数是否为空*/
bool LinkedList_IsEmpty(ManNode_t *Manager);


/*链表尾插*/
bool LinkedList_TailInsert(ManNode_t *Manager, Info_t *fInfo);

/*链表头插*/
bool LinkedList_HeadInset(ManNode_t *Manager, Info_t *fInfo);


/*链表遍历打印*/
void LinkedList_PrintNode(ManNode_t *Manager);

/*结点查找*/
// Node_t *LinkedList_FindNode(ManNode_t *Manager, int FNum);//返回在链表找到的第一个结点地址

/*结点搜索*/
// void LinkedList_SearchNode1(ManNode_t *Manager, int fNum);

/*链表删除*/
bool LinkedList_DelNode(ManNode_t *Manager, char *fNum);

#endif
