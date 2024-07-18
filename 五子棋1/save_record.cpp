#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void save_record(int a)   //a接收前面传来的flag的值
{ 
	FILE* pf;     //文件指针
	pf = fopen("AI.txt", "a");   //打开AI.txt文件
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	//a为偶数，表示AI赢了
	if (a % 2 == 0)
	{ 
		fputs("与AI对战====", pf);
		fputs("AI胜利，玩家惜败！\n", pf);
	}
	//a为奇数，表示玩家赢了
	else if (a % 2 == 1)
	{
		fputs("与AI对战====", pf);
		fputs("玩家胜利！\n", pf);
	}
	fclose(pf);   //关闭文件
	pf == NULL;   //将文件指针置为空
}