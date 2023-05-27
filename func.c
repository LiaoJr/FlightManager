#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include"list.h"


int ShowMenu()
{
    // system("clear");
	int choice;
	
	printf("==============================Welcome to flight management system===========================\n");
	printf("|                                                                                          |\n");
	printf("|    1. Input flight Infomation.(录入信息)                                                  |\n");
	printf("|    2. Print flight Infomation.(打印信息)                                                  |\n");
	printf("|    3. Search flight.(搜索信息)                                                            |\n");                                                           
	printf("|    4. Delete flight Infomation.(删除信息)                                                 |\n");
	printf("|    5. Sort Flight Infomation.(排序信息)                                                   |\n");
	printf("|    6. save and exit.(保存并退出程序)                                                                     |\n");
	printf("|                                         感谢使用                                          |\n");
	printf("|------------------------------------------------------------------------------------------|\n");
	printf("|>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>Please Input your choice:");
	scanf("%d", &choice);
	printf("\n  \n");

	return choice;
}


bool FlightInfo_Read(ManNode_t *manager)
{
    system("clear");

	char fp[64] = "FlightInfo.txt";
	FILE *f = fopen(fp, "r");
	if(NULL == f){
		perror("file fopen failed.");
		return false;
	}

	// int fscanf(FILE *stream, const char *format, ...);
	// char FlightNum[8], price[8], time[64], start[64], dest[64], board[4];
	Node_t ReadTmp;
	int R;
	while(true){
		R = fscanf(f, "%s %s %s %s %s %s\n",
					ReadTmp.Info.FilghtNum,
					ReadTmp.Info.price,
					ReadTmp.Info.time,
					ReadTmp.Info.start,
					ReadTmp.Info.dest,
					ReadTmp.Info.board);

        if(R == EOF){
            break;
        }

		/*将读到的数据打印出来看看*/
        printf("No:%-4s | Time:%-10s | Start place:%-10s | Destiny:%-10s | Boarding port:%-3s | Price:%-s \n", 
				ReadTmp.Info.FilghtNum, 
				ReadTmp.Info.time, 
				ReadTmp.Info.start, 
				ReadTmp.Info.dest, 
				ReadTmp.Info.board, 
				ReadTmp.Info.price);
        
        LinkedList_TailInsert(manager, &ReadTmp.Info);
	}

	int cn = fclose(f);
	if(cn != 0){
		perror("file fclose failed.");
		return false;
	}

    printf("Read Flight Infomation from %s success.\n", fp);
    printf("文件信息读取成功!\n");
    return true;
}

/*录入航班信息*/
void FlightInfo_Input(ManNode_t *manager)
{
	Info_t temp;
    bool ContiFlag;

    system("clear");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>Input Flight Infomation>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    while(1){
        printf("Please input infomation: \n");
        printf("Flight Number: ");
        scanf("%s", (temp.FilghtNum));
        getchar(); //清除输入缓存区
        // printf("\n");
        
        printf("price: ");
        scanf("%s", temp.price);
        getchar(); //清除输入缓存区
        
        printf("Fly time(format: 2023-05-20 .e.g): ");
        scanf("%s", temp.time);
        getchar(); //清除输入缓存区
        
        printf("Start place: ");
        scanf("%s", temp.start);
        getchar(); //清除输入缓存区
        
        printf("Destiny: ");
        scanf("%s", temp.dest);
        getchar(); //清除输入缓存区
        
        printf("Boarding Number: ");
        scanf("%s", temp.board);
        getchar(); //清除输入缓存区
        
        char sure;
        printf("Are you sure?(y/n)");
        scanf("%c", &sure);
        printf("------Your choice: %c------\n", sure);
        if(sure != 'y'){
            printf("Please input a new one.\n");
            continue;
        }

        LinkedList_TailInsert(manager, &temp);

        while(true){
            char conti;
            // getchar();  //清掉输入缓存区字符'\n'
            scanf("%*c");  //清空输入换缓存区 
            printf("Continue Input the next Flight infomation(y/n):");
            scanf("%c", &conti);
            printf("------your input: %c-----\n", conti);
            if(conti == 'n'){
                ContiFlag = false;
                break;
            }
            else if(conti == 'y'){
                ContiFlag = true;
                break;
            }
            else{
                printf("Invalid Input.\n");
                continue;
            }
        }

        if(ContiFlag){
            continue;
        }
        else{
            break;
        }
    }
}


void FlightInfo_Print(ManNode_t *manager)
{
	int back;
    system("clear");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>Print Flight Infomation>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	LinkedList_PrintNode(manager);
	while(1){
		printf(">>>>>>>>>>Input 0 back to main menu:");
		scanf("%d", &back);
		if(back==0){
			return;
		}
		else{
			printf("Invalid Input, please input again.\n");
		}

	}
}


void PrintNodeInfo(Node_t *NodeFind)
{

    printf("No:%-2s | Time:%-10s | Start place:%-10s | Destiny:%-10s | Boarding port:%-3s | Price:%-4s \n", 
            NodeFind->Info.FilghtNum, 
            NodeFind->Info.time, 
            NodeFind->Info.start, 
            NodeFind->Info.dest, 
            NodeFind->Info.board, 
            NodeFind->Info.price);

}




Node_t *SearchByPrice(Node_t *Node, char *price)
{
    Node_t *NodeFind = Node;
    while(NodeFind != NULL){
        if(0 == strcmp(NodeFind->Info.price, price)){
            return NodeFind;
        }
        NodeFind = NodeFind->next;
    }

    return NULL;
}


Node_t *SearchByNum(Node_t *Node, char *num)
{
    Node_t *NodeFind = Node;
    while(NodeFind != NULL){
        if(0 == strcmp(NodeFind->Info.FilghtNum, num)){
            return NodeFind;
        }
        NodeFind = NodeFind->next;
    }

    return NULL;
}

Node_t *SearchByTime(Node_t *Node, char *time)
{
    Node_t *NodeFind = Node;
    while(NodeFind != NULL){
        if(0 == strcmp(NodeFind->Info.time, time)){
            return NodeFind;
        }
        NodeFind = NodeFind->next;
    }

    return NULL;
}


Node_t *SearchByStartPlace(Node_t *Node, char *startplace)
{
    Node_t *NodeFind = Node;
    while(NodeFind != NULL){
        if(0 == strcmp(NodeFind->Info.start, startplace)){
            return NodeFind;
        }
        NodeFind = NodeFind->next;
    }

    return NULL;
}


Node_t *SearchByDestiny(Node_t *Node, char *destiny)
{
    Node_t *NodeFind = Node;
    while(NodeFind != NULL){
        if(0 == strcmp(NodeFind->Info.dest, destiny)){
            return NodeFind;
        }
        NodeFind = NodeFind->next;
    }

    return NULL;
}

Node_t *SearchByBoard(Node_t *Node, char *BoardNum)
{
    Node_t *NodeFind = Node;
    while(NodeFind != NULL){
        if(0 == strcmp(NodeFind->Info.board, BoardNum)){
            return NodeFind;
        }
        NodeFind = NodeFind->next;
    }

    return NULL;
}


/*根据航班号查找航班*/  //第二个参数是一个函数指针
void FlightInfo_Search(ManNode_t *manager)
{
	int back;
    Node_t *NodeFind;
    system("clear");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>Search Flight Infomation>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    bool ContiFlag;


    int choice;
	while(1){
        int FlagFind = 0;
        printf("Search by?\n");
        printf("==>1.Flight Num.\n");
        printf("==>2.Price.\n");
        printf("==>3.Start time.\n");
        printf("==>4.Start place.\n");
        printf("==>5.Destiny.\n");
        printf("==>6.Boarding Port.\n");
        printf("Please input your choice?");
        scanf("%*c");
        scanf("%d", &choice);

        switch(choice){
            /*根据航班号搜索*/
            case 1: 
                char flightNum[8];
                printf(">>>>>>>>>>Plaese input a flight number:");
                scanf("%*c");
                scanf("%s", flightNum);

                printf("==========================================Search result===========================================\n");
                NodeFind = manager->Head;
                while(NodeFind != NULL){
                    NodeFind = SearchByNum(NodeFind, flightNum);
                    if(NULL == NodeFind){
                        break;
                    }
                    PrintNodeInfo(NodeFind);
                    NodeFind = NodeFind->next;
                    FlagFind++;
                }
                printf("====================================================================================================\n\n");
                break;

            case 2: ;
                char price[8];
                printf(">>>>>>>>>>Plaese input a flight price:");
                scanf("%*c");
                scanf("%s", price);

                printf("==========================================Search result===========================================\n");
                NodeFind = manager->Head;
                while(NodeFind != NULL){
                    NodeFind = SearchByPrice(NodeFind, price);
                    if(NULL == NodeFind){
                        break;
                    }
                    PrintNodeInfo(NodeFind);
                    NodeFind = NodeFind->next;
                    FlagFind++;
                }
                printf("====================================================================================================\n\n");
                break;

            case 3: ;
                char time[64];
                printf(">>>>>>>>>>Plaese input a flight time:");
                scanf("%*c");
                scanf("%s", time);

                printf("==========================================Search result===========================================\n");
                NodeFind = manager->Head;
                while(NodeFind != NULL){
                    NodeFind = SearchByTime(NodeFind, time);
                    if(NULL == NodeFind){
                        break;
                    }
                    PrintNodeInfo(NodeFind);
                    NodeFind = NodeFind->next;
                    FlagFind++;
                }
                printf("====================================================================================================\n\n");
                break;

            case 4: ;
                char startplace[8];
                printf(">>>>>>>>>>Plaese input a flight start place:");
                scanf("%*c");
                scanf("%s", startplace);

                printf("==========================================Search result===========================================\n");
                NodeFind = manager->Head;
                while(NodeFind != NULL){
                    NodeFind = SearchByStartPlace(NodeFind, startplace);
                    if(NULL == NodeFind){
                        break;
                    }
                    PrintNodeInfo(NodeFind);
                    NodeFind = NodeFind->next;
                    FlagFind++;
                }
                printf("====================================================================================================\n\n");
                break;

            case 5: ;
                char destiny[8];
                printf(">>>>>>>>>>Plaese input a flight destiny:");
                scanf("%*c");
                scanf("%s", destiny);

                printf("==========================================Search result===========================================\n");
                NodeFind = manager->Head;
                while(NodeFind != NULL){
                    NodeFind = SearchByDestiny(NodeFind, destiny);
                    if(NULL == NodeFind){
                        break;
                    }
                    PrintNodeInfo(NodeFind);
                    NodeFind = NodeFind->next;
                    FlagFind++;
                }
                printf("====================================================================================================\n\n");
                break;

            case 6: ;
                char board[8];
                printf(">>>>>>>>>>Plaese input a flight board number:");
                scanf("%*c");
                scanf("%s", board);

                printf("==========================================Search result===========================================\n");
                NodeFind = manager->Head;
                while(NodeFind != NULL){
                    NodeFind = SearchByBoard(NodeFind, board);
                    if(NULL == NodeFind){
                        break;
                    }
                    PrintNodeInfo(NodeFind);
                    NodeFind = NodeFind->next;
                    FlagFind++;
                }
                printf("====================================================================================================\n\n");
                break;

            default: printf("Invalid input.\n");
        }

        if(FlagFind == 0){
            printf("Flight Infomation not found.\n");
        }

        char conti;
        while(1){
            printf("Continue to search the next infomation?(y/n):");
            scanf("%*c");
            scanf("%c", &conti);
            if(conti == 'y'){
                ContiFlag = true;
                break;
            }
            else if(conti == 'n'){
                ContiFlag = false;
                break;
            }
            else{
                printf("Invalid Input please input again.\n");
            }
        }

        if(!ContiFlag){
            break;
        }
	}

    while(1){
		printf(">>>>>>>>>>Input 0 back to main menu:");
		scanf("%d", &back);
		if(back==0){
			return;
		}
		else{
			printf("Invalid Input, please input again.\n");
		}
    }
}



void FlightInfo_Delete(ManNode_t *manager)
{
	char num[8];
	bool ret;
    system("clear");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>Delete Flight Infomation>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    int ContiFlag = 0;
    while(1){
        LinkedList_PrintNode(manager);
        printf("Please input a flight number which you want to delete: ");
        scanf("%s", num);
        printf("\n");

        ret = LinkedList_DelNode(manager, num);
        if(ret){
            printf("Flight %s has been deleted. \n", num);
        }
        else{
            printf("Can not delete your flight infomation.\n");
        }

        char conti;
        while(1){
            printf("Continue to delete more?(y/n):");
            scanf("%*c");
            scanf("%c", &conti);
            if(conti == 'y'){
                ContiFlag = true;
                break;
            }
            else if(conti == 'n'){
                ContiFlag = false;
                break;
            }
            else{
                printf("Invalid Input please input again.\n");
            }
        }

        if(!ContiFlag){
            break;
        }
        sleep(2);

    }
}


/*根据时间排序*/
void FlightInfo_Sort(ManNode_t *manager)
{
    system("clear");
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>Sort Flight Infomation>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    /*使用插入排序*/
    int len=0;  //获取链表长度
    Node_t *NodeTemp = manager->Head, *NodeTempPrev;
    Node_t *NodeCmp, *NodeCmpPrev;
    while(NodeTemp != NULL){
        len++;
        NodeTemp = NodeTemp->next;
    }

    printf(">>>>>>>>>>Sorting...\n");
    /*如果链表长度小于2，直接返回*/
    if(len < 2){
        return ;
    }

    Node_t *NodeCurNext, *NodeCur;
    NodeTemp = manager->Head->next;  
    NodeTempPrev = manager->Head;
    for(int i=2;i <= len; i++){
        NodeCmp = manager->Head;
        NodeCmpPrev = NULL;
        for(int j=1;j < i;j++){
            /*如果NodeTemp小于NodeCmp，则NodeTemp插到NodeCmp的前面*/
            if(strcmp(NodeTemp->Info.time, NodeCmp->Info.time) < 0){
                if(NodeCmpPrev == NULL){  //如果是要插到首节点前面
                    NodeCurNext = NodeTemp->next;

                    NodeTempPrev->next = NodeTemp->next;
                    NodeTemp->next = NodeCmp;
                    manager->Head = NodeTemp;

                    NodeCur = manager->Head;
                    while(NodeCur->next != NodeCurNext){
                        NodeCur = NodeCur->next;
                    }

                    //此时NodeCurNext放的是下一轮的NodeTemp(也就是要插的那个)
                    //此时NodeCur放的是下一轮的NodeTempPrev(也就是要插的那个的前驱)

                    break;
                }
                else{
                    NodeCurNext = NodeTemp->next;

                    NodeTempPrev->next = NodeTemp->next;
                    NodeCmpPrev->next = NodeTemp;
                    NodeTemp->next = NodeCmp;

                    NodeCur = manager->Head;
                    while(NodeCur->next != NodeCurNext){
                        NodeCur = NodeCur->next;
                    }

                    //此时NodeCurNext放的是下一轮的NodeTemp(也就是要插的那个)
                    //此时NodeCur放的是下一轮的NodeTempPrev(也就是要插的那个的前驱)
                    break;
                }
            }
            else{  //若NodeTemp大于或等于NodeCmp
                NodeCmpPrev = NodeCmp;
                NodeCmp = NodeCmp->next;
                NodeCurNext = NodeTemp->next;
                NodeCur = NodeTemp;
            }
        }

        NodeTempPrev = NodeCur;
        NodeTemp = NodeCurNext;
    }
}


bool FlightInfo_Save(ManNode_t *manager)
{
    char fp[64] = "FlightInfo.txt";
    FILE *f = fopen(fp, "w+");
    if(NULL == f){
        perror("file fopen failed.");
        return false;
    }

    // int fprintf(FILE *stream, const char *format, ...);
    Node_t *NodeSave = manager->Head;
    while(NodeSave != NULL){
        fprintf(f, "%s %s %s %s %s %s\n", 
        NodeSave->Info.FilghtNum, 
        NodeSave->Info.price,
        NodeSave->Info.time,
        NodeSave->Info.start,
        NodeSave->Info.dest,
        NodeSave->Info.board);

        NodeSave = NodeSave->next;
    }

    int cn = fclose(f);
    if(cn != 0){
        perror("file fclose failed.");
        return false;
    }
    printf("Flight Infomation save success.\n");
    printf("文件信息保存成功!\n");

    return true;
}

