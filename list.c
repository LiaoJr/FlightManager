/*
设计一个航班管理系统实现航班的增删改查和排序（价格排序，起飞时间排序）。
结构体中包含，价格，航班号，起飞时间，出发地，目的地，值机柜台，登机口，预计起飞时间。 
 */


//使用到头结点的单向链表实现
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"list.h"


/*链k表创建函数*/
ManNode_t * LinkedList_Create(void)
{
    /*申请堆内存存贮管理头结点, 用于记录链表信息*/
    ManNode_t *Manager = (ManNode_t *)calloc(1, sizeof(ManNode_t));
    if(NULL == Manager){
        perror("Memory for Manager calloc failed!");
        return NULL;
    }

    /*初始化管理结构体*/
    Manager->NodeNum = 0;  //记录链表有效节点的数量
    Manager->Head = NULL;  //记录链表的首节点的地址
    Manager->Tail = NULL;  //记录链表尾节点的地址

    return Manager;
}

/*创建新节点函数*/
Node_t * LinkedList_NewNode(Info_t *fInfo)
{
    /*为结点申请空间*/
    Node_t *NewNode = (Node_t *)calloc(1, sizeof(Node_t));
    if(NULL == NewNode){
        perror("calloc For NewNode Failed.");
        return NULL;
    }

    /*初始化头结点*/
	strcpy(NewNode->Info.FilghtNum, fInfo->FilghtNum);
	strcpy(NewNode->Info.price, fInfo->price);
	strcpy(NewNode->Info.time, fInfo->time);
	strcpy(NewNode->Info.start, fInfo->start);
	strcpy(NewNode->Info.dest, fInfo->dest);
	strcpy(NewNode->Info.board, fInfo->board);

    NewNode->next = NULL;

    /*返回头结点的地址*/
    return NewNode;
}


/*判断链表是否为空*/
bool LinkedList_IsEmpty(ManNode_t *Manager)
{
    /*根据链表的节点数量进行判断*/
    return (Manager->NodeNum == 0) ? true : false;

    /*根据头结点的首结点地址进行判断*/
    // return (Manager->Head == NULL) ? true : false;
}

bool LinkedList_TailInsert(ManNode_t *Manager, Info_t *fInfo)
{
    ManNode_t *pManager = Manager;
    /*创建新节点*/
    Node_t *NewNode = LinkedList_NewNode(fInfo);
    if(NULL == NewNode){
        perror("Create New Node Failed.");
        return false;
    }

    /*如果链表中是空的，则新节点设为首节点*/
    if(LinkedList_IsEmpty(Manager)){
        pManager->Head = NewNode;
        pManager->Tail = NewNode;
        pManager->NodeNum++;
    }
    else{
        pManager->Tail->next = NewNode;  //原尾结点的指针指向新加入的结点
        pManager->Tail = NewNode;  //更新头结点中记录尾节点地址的成员
        pManager->NodeNum++;       //更新头结点中记录链表节点数量的成员
    }

	return true;
}

bool LinkedList_HeadInset(ManNode_t *Manager, Info_t *fInfo)
{
    Node_t *NewNode = LinkedList_NewNode(fInfo);
    if(NULL == NewNode){
        printf("Create New Node Failed.");
        return false;
    }

    /*如果链表中是空的，则新节点设为首节点*/
    ManNode_t *pManager = Manager;
    if(LinkedList_IsEmpty(Manager)){
        pManager->Head = NewNode;
        pManager->Tail = NewNode;
        pManager->NodeNum++;
    }
    else{
        NewNode->next = pManager->Head;  //新结点的next指针指向原首结点
        pManager->Head = NewNode;        //
        pManager->NodeNum++;
    }

	return true;
}

void LinkedList_PrintNode(ManNode_t *Manager)
{
    Node_t *NodePrint = Manager->Head;  

	printf("============================================Flight Infomation==========================================\n");
	printf("Total flight number: %d\n", Manager->NodeNum);
    while(NodePrint){
        printf("No:%-4s | Time:%-10s | Start place:%-10s | Destiny:%-10s | Boarding port:%-3s | Price:%-s \n", 
				NodePrint->Info.FilghtNum, 
				NodePrint->Info.time, 
				NodePrint->Info.start, 
				NodePrint->Info.dest, 
				NodePrint->Info.board, 
				NodePrint->Info.price);

        NodePrint = NodePrint->next;
    }
	printf("=======================================================================================================\n");
}


/*链表结点查找(根据航班号查找)*/
// Node_t *LinkedList_FindNode(ManNode_t *Manager, int FNum)
// {
//     Node_t *NodeFind = Manager->Head;  
// 	int NumFind=0;

//     while(NodeFind){
// 		/*如果找到了结点*/
// 		if(NodeFind->Info.FilghtNum == FNum){
// 			NumFind++;
//             break;
// 		}
//         NodeFind = NodeFind->next;
//     }

//     /*如果一个都没找到*/
// 	if(NumFind == 0){
// 		return NULL;
// 	}
	
//     return NodeFind;  //返回在链表找到的第一个结点地址
// }



bool LinkedList_DelNode(ManNode_t *Manager, char *fNum)
{
    /*判断链表中是否存在节点*/
    if(LinkedList_IsEmpty(Manager)){
        printf("There is no node in the list!\n");
        return false;
    }

    /*判断当前链表中的节点的数据域是否有和目标值匹配*/
    Node_t *NodeDel = Manager->Head;
    Node_t *temp = NULL;  //记录要删除结点的直接前驱
    while(NodeDel){
        if(0 == strcmp(NodeDel->Info.FilghtNum, fNum)){
            break;
        }
        temp = NodeDel;  //记下要删除结点的直接前驱
        NodeDel = NodeDel->next;
    }

    /*没找到目标结点*/
    if(NULL == NodeDel){
        printf("Can not find the node you want to delete.\n");
        return false;
    }

    /*若要删除的结点刚好是首节点*/
    if(NodeDel == Manager->Head){
        Manager->Head = NodeDel->next;
        NodeDel->next = NULL;  //防止野指针出现
        free(NodeDel);
        Manager->NodeNum--;
    }
    else{
        /*若要删除的结点刚好是尾节点*/
        if(NodeDel == Manager->Tail){
            Manager->Tail = temp;
            temp->next = NULL;
            NodeDel->next = NULL;
            free(NodeDel);
            Manager->NodeNum--;
        }
        /*要删除的刚好是中间结点*/
        else{
            temp->next = NodeDel->next;
            NodeDel->next = NULL;
            free(NodeDel);  
            Manager->NodeNum--;
        }
    }
    return true;
}

