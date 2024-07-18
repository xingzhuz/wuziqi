#include "game.h"
//void BGM();
//void BGM()
//{
//	mciSendString("open ./星茶会.mp3", 0, 0, 0);
//	mciSendString("play ./星茶会.mp3", 0, 0, 0);
//}


void main()
{
	//绘图环境
	initgraph(500, 749);
	//贴图
	loadimage(NULL, "menu.jpg");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	//画四个开始界面
	setfillcolor(BROWN);     //圆角矩形的填充颜色
	//四个圆角矩形的位置
	fillroundrect(170, 310, 320, 360, 10, 10);    
	fillroundrect(170, 380, 320, 430, 10, 10);
	fillroundrect(170, 450, 320, 500, 10, 10);
	fillroundrect(170, 520, 320, 570, 10, 10);
	settextstyle(30, 0, "行楷");         //圆角矩形内字体的样式及大小
	//四个圆角矩形内的字体内容
	outtextxy(198,321, "AI对战");        
	outtextxy(185,391, "双人对战");
	outtextxy(185,461, "查看战绩");
	outtextxy(185,531, "退出游戏");
	//BGM();    //插入音乐

	MOUSEMSG n;
	while (1)
	{
		n = GetMouseMsg();
		//这是对鼠标点击位置的确定，然后进入不同的函数，实现不同的功能
		if (n.uMsg == WM_LBUTTONDOWN)
		{   
			if (n.x > 170 && n.x < 320 && n.y>310 && n.y < 360)
			{
				AI();    //进入AI对战
				break;
			}
			else if (n.x > 170 && n.x < 320 && n.y>380 && n.y < 430)
			{
				player();   //进入双人对战
				break;
			}
			else if (n.x > 170 && n.x < 320 && n.y>450 && n.y < 500)
			{
				load_record();  //进入查看战绩
				break;
			}
			else if (n.x > 170 && n.x < 320 && n.y>520 && n.y < 570)
			{
				exit(0);     //退出游戏
			}
		}
	}
	main();    //再次进入游戏主界面菜单
}
