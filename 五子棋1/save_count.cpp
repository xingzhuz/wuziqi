#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

int save_count(int j)    //j用来接收之前下棋的总次数
{
	int count1 = 0;    //作为存储下棋次数的变量
	FILE* pn = fopen("AI.dat", "w");    //打开AI.dat文件
	if (pn == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	//写入东西在文件里
	count1 = j + 1;     //下完一次棋就将总次数加一
	fwrite(&count1, 4, 1, pn);  //将现在的总次数写入AI.dat文件里
	                            //求总次数是为了能更好的访问AI.txt里的每行战绩
 	fclose(pn);            //关闭AI.dat文件
	pn = NULL;       //将文件指针置为空
	return 0;
}