#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

int load_count()
{
	int count2 = 0;
	FILE* pm = fopen("AI.dat", "r");     //将AI.dat文件打开，进行只读的操作
	if (pm == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	//读文件
	fread(&count2, 4, 1, pm);      //读取AI.dat文件里的数据赋给count2
	fclose(pm);                    //关闭文件
	pm = NULL;                     //将文件指针置为空
	return count2;                //将读取到的count2数据返回
}