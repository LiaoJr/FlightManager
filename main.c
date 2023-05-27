#include<stdio.h>
#include<unistd.h>
#include"list.h"
#include"func.h"



int main()
{
	int choice;

	/*创建一个空链表*/
	ManNode_t *pManager = LinkedList_Create();
	/*----------------------测试用，因为每次都输入比较麻烦-------------------*/
#if 0
    Info_t f1 = {
        "200",
        "1",
        "2023-06-11",
        "GuangZhou",
        "New York",
        "A26"
    };
    Info_t f2 = {
        "300",
        "2",
        "2023-01-15",
        "ZhongShan",
        "London",
        "A12"
    };
    Info_t f3 = {
        "472",
        "3",
        "2023-09-12",
        "Paris",
        "Madrid",
        "B12"
    };
    Info_t f4 = {
        "1272",
        "4",
        "2023-11-28",
        "Manchester",
        "Milan",
        "U09"
    };
    LinkedList_TailInsert(pManager, &f1);
    LinkedList_TailInsert(pManager, &f2);
    LinkedList_TailInsert(pManager, &f3);
    LinkedList_TailInsert(pManager, &f4);
#endif
	/*--------------------------------------------------------------------------*/

	/*将文件FlightInfo.txt中的信息读入系统中*/
	FlightInfo_Read(pManager);

	bool ExitFlag = false;
	while(1){
		choice = ShowMenu();
		printf("-----------Your choice: %d----------\n", choice);
		switch(choice){
			//录入航班信息
			case 1: FlightInfo_Input(pManager);
					break;

			//打印航班信息
			case 2: FlightInfo_Print(pManager);
					break;
			
			//搜索航班信息
			case 3: FlightInfo_Search(pManager);
					break;

			//删除航班信息
			case 4: FlightInfo_Delete(pManager);
					break;

			//根据起飞时间排序
			case 5: FlightInfo_Sort(pManager);
					FlightInfo_Print(pManager);
					break;

			//保存信息到文件并退出
			case 6:
					char cho;
					bool FlagSaveBreak = false;
					while(!FlagSaveBreak){
						printf("Save the infomation or not?(y/n)"); 
						scanf("%*c");
						scanf("%c", &cho);
						if(cho == 'y'){
							FlagSaveBreak = true;
							FlightInfo_Save(pManager);
						}
						else if(cho == 'n'){
							break;
						}
						else{
							printf("Invalid input, please input again.\n");
						}
					}
					ExitFlag = true; 
					break;
			
			default: printf("Invalid input, please input the right number.\n");
					 sleep(3);
		}

		if(ExitFlag){
			printf("Thanks for your using, bye bye~~\n");
			break;
		}

	}
}
