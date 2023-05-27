#include<stdio.h>


typedef struct info{
	int price;      //价格
	int FilghtNum;  //航班号
	char time[64];  //起飞时间
	char start[64]; //出发地
	char dest[64];  //目的地
	char board[4];  //登机口
	
}Info_t;

enum letter{A, B, C};

int main()
{
	int a,b,c=3;
	a=b=c+2;
	printf("a=%d, b=%d, c=%d\n", a, b, c);
	printf("leter = %d\n", A);
	int num;
	scanf("%d", &num);
	printf("num = %d\n", num);

	scanf("%d", &num);
	printf("num = %d\n", num);

	return 0;
}
