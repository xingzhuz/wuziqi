#define _CRT_SECURE_NO_WARNINGS
#include "game.h"



void load_record()
{
	//图形窗口大小
	initgraph(670, 900);
	loadimage(NULL, "record.jpg");
	//BGM();
	setbkmode(TRANSPARENT);
	setfillcolor(YELLOW);
	fillrectangle(45, 50, 155, 100);
	fillrectangle(535, 50, 645, 100);
	settextstyle(24, 0, "楷体");
	settextcolor(BLACK);
	outtextxy(55, 60, "返回菜单");
	outtextxy(542, 60, "退出游戏");
	

	int m = 1;
	int v = 0;       
	v = load_count();  //将AI.dat文件里的下棋次数存储到V
	int i;
	char buf[200] = { 0 };
	FILE* pt = fopen("AI.txt","r");   //打开AI.txt文件，并进行读的操作
	if (pt == NULL)
	{
		return;
	}
	//读文件
	settextstyle(20,0, "行楷");    //输出的战绩的字体样式
	settextcolor(BLACK);            //输出的字体颜色
	setbkmode(TRANSPARENT);        //输出的字体背景为透明
	int h = 150;
	for (i = v;i > 0;i--)
	{
		//由于字符输出只能是10以内的字符，所以超过10需要进行如下操作
		if (m < 10)
		{
			outtextxy(160, h, '0' + m);        //在0，h输出m变量所指的值
		}
		if (m >= 10)
		{
			outtextxy(155, h, '0' + m / 10);     //在0，h输出m变量所指的值的十位数
			outtextxy(165, h, '0' + m % 10);     //在0，h输出m变量所指的值的个位数
		}
		fgets(buf, 200, pt);          //读取AI.txt文件整行的数据
		outtextxy(200, h, buf);      //在100，h输出读取到的数据
		h =h +25;                    //执行将数据进行跳行的操作
		m++;                         //这是第m++次下的棋的战绩
	}
	
	fclose(pt);            //关闭文件
	pt == NULL;            //将文件指针置为空
	MOUSEMSG a;
	while (1)
	{
		a = GetMouseMsg();
		if (a.uMsg == WM_LBUTTONDOWN)
		{
			if (a.x > 45 && a.x < 155 && a.y>50 && a.y < 100)
			{
				break;
			}
			if (a.x > 535 && a.x < 645 && a.y>50 && a.y < 100)
			{
				exit(0);
			}
		}
	}

	return;
}