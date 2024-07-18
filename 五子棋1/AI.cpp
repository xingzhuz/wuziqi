#include "game.h"

int count1 = 0;       //记录玩家的胜负状况
int count2 = 0;       //记录AI的胜负状况
int step1 = 0;        //记录玩家走了的步数
int step2 = 0;        //记录AI走了的步数
int j = -1;           //作为与AI对战存储下棋次数的变量
int flag1 = 0;              //表示下棋的次数 
                             //flag为偶数表示电脑刚下完棋
                             //flag为奇数表示玩家刚下完棋

int board1[23][24] = { 0 };  //0表示没有棋子状态
                             //1表示这里有玩家的棋子
                             //2表示这里有电脑的棋子

HWND hwnd;
//AI对战的主函数
void AI()
{
	initGame1();   //进入初始化游戏
	while (1)
	{
		playerplaychess();   //进入AI下棋主函数
		break;
	}
}

//初始化游戏
void initGame1()
{
	
	//绘图环境
	hwnd=initgraph(670, 650);      //图形窗口大小为600x500
	//贴图
	loadimage(NULL, "chess.jpg");
	//BGM();
	setlinecolor(BLACK);        //画的棋盘线为蓝色
	//绘制棋盘
	//画线
	for (int i = 25;i <= 525;i += 25)
	{
		line(i+25, 75, i+25, 575);
		line(50, i+50, 550, i+50);
	}

	//在棋盘中央打印五个黑色小点小点
	setfillcolor(BLACK);             //棋盘上画的小点的填充颜色
	solidcircle((10 + 2) * 25, (10 + 3) * 25, 5);
	solidcircle((6 + 2) * 25, (14 + 3) * 25, 5);
	solidcircle((14 + 2) * 25, (14 + 3) * 25, 5);
	solidcircle((6 + 2) * 25, (6 + 3) * 25, 5);
	solidcircle((14 + 2) * 25, (6 + 3) * 25, 5);

	//棋盘右边字符串的操作
	setbkmode(TRANSPARENT);            //输出的字符串背景为透明
	setfillcolor(LIGHTGRAY);          //圆角矩形的填充颜色
	fillroundrect(560, 140, 660, 180, 10, 10);    //画圆角矩形
	settextcolor(BLACK);                         //打印出棋盘右边的文字的颜色
	settextstyle(20, 0, "黑体");                 //棋盘右边文字的大小及样式
	outtextxy(565, 150, "玩家:黑棋");            //在棋盘右边打印出电脑所执棋颜色
	fillroundrect(560, 240, 660, 280, 10, 10);   //画圆角矩形
	outtextxy(565, 250, "玩家:白棋");            //在棋盘右边打印出玩家所执棋颜色

	settextstyle(35, 0, "楷体");                 //打印出棋盘右边VS这个字符串的大小，样式
	settextcolor(RED);                          //打印出棋盘右边VS为红色
	outtextxy(590, 192, "VS");                   //打印出VS这个字符串
	

	//在棋盘顶上打印的文字
	settextstyle(27, 0, "楷体");                 //在棋盘顶上的文字的大小及样式
	settextcolor(BLACK);                         //在棋盘顶上的文字的颜色为黑色
	setfillcolor(GREEN);                         //在棋盘顶上画的矩形框的填充颜色为绿色
	outtextxy(45, 10, "电脑：黑棋");             
	outtextxy(45, 40, "步数：");
	fillrectangle(130, 40, 180, 70);            //画的矩形矩形框
	outtextxy(148, 42, '0' + 0);                //用字符‘0’+数字转换为数字字符进而进行输出，这样可以输出变化的数字
	outtextxy(520, 10, "AI：白棋");
	outtextxy(500, 40, "步数：");
	fillrectangle(580, 40, 635, 70);            //画的矩形框
	outtextxy(600, 42, '0' + 0);
	
	//在棋盘顶上打印胜负状况
	outtextxy(280, 10, "玩家:");
	outtextxy(355, 10, " AI");
	//由于字符只能输出10以内字符，所以需要进行如下操作
	//这是如果玩家胜场数超过10后的处理
	if (count1 < 10)
	{
		outtextxy(300, 40, '0' + count1);    //打印出玩家的胜场数
	}
	if (count1 >= 10)
	{
		outtextxy(292, 40, '0' + count1 / 10);    //打印出玩家的胜场数的十位数
		outtextxy(306, 40, '0' + count1 % 10);    //打印出玩家的胜场数的个位数
	}
	//这是电脑胜场数超过10后的处理
	if (count2 < 10)
	{
		outtextxy(336, 40, ":");        
		outtextxy(370, 40, '0' + count2);        //打印出AI的胜场数
	}
	if (count2 >= 10)
	{
		outtextxy(336, 40, ":");
		outtextxy(366, 40, '0' + count2 / 10);    //打印出AI的胜场数的十位数
		outtextxy(380, 40, '0' + count2 % 10);    //打印出AI的胜场数的个位数
	}

	//棋盘底部的文字，表示玩家可以进行的操作
	setfillcolor(YELLOW);              //矩形框的填空颜色
	settextstyle(23,0, NULL);           //矩形框内文字的大小及样式
	fillrectangle(35, 600, 140, 630);    //画的几个矩形框
	fillrectangle(535, 600, 640, 630);
	fillrectangle(265, 600, 395, 630);
	outtextxy(40, 605, "重新开始");      //矩形框内的文字
	outtextxy(540, 605, "退出游戏");
	outtextxy(270, 605, "退出AI对战");
}


//玩家下棋
void playerplaychess()
{
	int a = 0, b = 0;
	//鼠标
	MOUSEMSG m;     //保留鼠标消息
	while (1)
	{
		m = GetMouseMsg();    //获取一个鼠标消息
		
		//防止鼠标点哪棋子就在哪，而不是在线格子交线处
		for (int i = 2;i < 23;i++)
		{
			for (int j = 3;j < 24;j++)
			{
				//加个abs函数求绝对值，使其每次只需要点击交线处旁边范围即可，就能够下在交线处
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)
				{
					a = i;
					b = j;
				}
			}
		}
		//鼠标点击后
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//判断玩家是否需要进行重新开始、退出AI对战、退出游戏操作
			if (m.x > 35 && m.x < 140 && m.y>600 && m.y < 630)     //这是重新开始AI对战的矩形范围
			{
				//这个for循环是为了将全局变量数组初始化为0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board1[i][j] = 0;
					}
				}
				step1 = 0, step2 = 0;       //之前记录的步数把它赋值为0
				AI();    //再次进入AI对战
			}
			if (m.x > 535 && m.x < 640 && m.y>600 && m.y < 630)    //这是退出游戏的矩形框范围
			{
				exit(0);  //退出游戏
			}
			if (m.x > 265 && m.x < 395 && m.y>600 && m.y < 630)    //这是退出AI对战的矩形框范围
			{
				//这个for循环是为了将全局变量数组初始化为0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board1[i][j] = 0;
					}
				}
				step1 = 0, step2 = 0;      //之前记录的步数把它赋值为0
				count1 = 0, count2 = 0;   //之前记录的胜负状况全把它赋值为0
				break;         //退出这个循环，为了结束这个AI对战，重新进入main()函数
			}

			//如果棋子重叠了的提示操作
			if (board1[a][b] != 0)
			{
				MessageBox(hwnd, "这里已经有棋子了，请重新选择", "提示", MB_OK);
				continue;   //退出循环重新进入
			}
			if (flag1 % 2 == 0)      //偶数
			{
				setfillcolor(BLACK);
				solidcircle(a * 25, b * 25, 10);
				board1[a][b] = 1;
			}
			step1++;    //玩家步数加一
			flag1++;   

			//打印玩家的步数
			setbkcolor(GREEN);     //背景颜色为绿色
			clearrectangle(130, 40, 180, 70);       //用填充颜色覆盖之前的步数
			//由于字符输出只能是10以内的字符，所以超过10需要进行如下操作
			if (step1 < 10)
			{
				outtextxy(148, 42, '0' + step1);    //打印出玩家的步数
			}
			if (step1 >= 10)
			{
				outtextxy(142, 42, '0' + step1 / 10);    //打印出玩家的步数的十位数
				outtextxy(154, 42, '0' + step1 % 10);    //打印出玩家的步数的个位数
			}

			//判断此时的输赢
			if (judge1() == 1)
			{
				if (flag1 % 2 == 1)
				{
					count1++;               //玩家赢了，记录它的变量加一 
					j = load_count();       //把储存下棋次数的文件夹打开，把值赋给j
					save_count(j);          //储存这一次的下棋次数进入save_count函数中AI.dat文件里
					save_record(flag1);     //把这一次AI对战的战绩存入文件AI.txt中

					//判断玩家是否需要继续AI对战
					int isok = MessageBox(hwnd, "玩家胜利,是否继续AI对战", "游戏结束", MB_OKCANCEL);
					if (isok == IDOK)
					{
						//这个for循环是为了将全局变量数组初始化为0
						for (int i = 2;i < 23;i++)
						{
							for (int j = 3;j < 24;j++)
							{
								board1[i][j] = 0;
							}
						}
						step1 = 0, step2 = 0;    //之前记录的步数把它赋值为0
						AI();       //再次进入AI对战
					}
					else if (isok == IDCANCEL)
					{
						exit(0);    //退出游戏
					}
				}
				
			}

			AIplaychess();       //AI下棋
			//判断此时的输赢
			if (judge1() == 1)
			{
				if (flag1 % 2 == 0)
				{
					count2++;                 //AI赢了，记录它的变量加一 
					j = load_count();         //把储存下棋次数的文件夹打开，把值赋给j
					save_count(j);            //储存这一次的下棋次数进入save_count函数中AI.dat文件里
					save_record(flag1);       //把这一次AI对战的战绩存入文件AI.txt中

					//判断玩家是否需要继续AI对战
					int isok1 = MessageBox(hwnd, "电脑胜利，是否继续AI对战", "游戏结束", MB_OKCANCEL);
					if (isok1 == IDOK)
					{
						//这个for循环是为了把全局变量数组初始化为0
						for (int i = 2;i < 23;i++)
						{
							for (int j = 3;j < 24;j++)
							{
								board1[i][j] = 0;
							}
						}
						step1 = 0, step2 = 0;    //之前记录的步数把它赋值为0
						AI();                //再次进入AI对战
					}
					else if (isok1 == IDCANCEL)
					{
						exit(0);
					}
				}
			}
		}
	}
}

//AI下棋一
void AIplaychess()
{
	int a,b,c,d,e,f,g,h,i,j;
	a = judge4();      //连续情况下判断电脑和玩家棋子将要为5时的应对
	if (a == 0)
	{ 
		f = judge6();    //不连续情况下判断电脑和玩家棋子将要为5时的应对
		if (f == 0)
		{
			i = judge9();   //连续情况下判断电脑棋子将要为4（为4后两旁都没有棋子堵住）
			if (i == 0)
			{
				j = judge10();   //不连续情况下判断玩家棋子将要为4时的应对（为4后两边棋子都没有电脑棋子堵住）
				if (j == 0)
				{                             
					e = judge3();    //连续情况下判断玩家棋子将要为4时的应对（为4后两边棋子都没有电脑棋子堵住） 
					if (e == 0)
					{
						b = judge5();   //不连续情况下判断电脑棋子将要为4时的应对（不管为4后两边之一是否有玩家棋子）         
						if (b == 0)
						{
							c = judge33();     //连续情况下判断电脑棋子为将要4时的应对（不管为4后两边之一是否有玩家棋子）  
							if (c == 0)
							{
								g = judge7();       //连续情况下判断电脑棋子将要为3时的应对
								if (g == 0)
								{
									h = judge8();      //连续情况下判断电脑棋子将要为2时的应对
									if (h == 0)
									{
										AIplaychess1();   //AI下棋二
									}
								}
							}
						}
					}
				}
			}
		}
	}
	flag1++;   //AI下完棋后，flag1++
	step2++;   //AI下完棋后，步数step1++

	//打印AI的步数
	setbkcolor(GREEN);      //步数矩形框的填充颜色
	clearrectangle(580, 40, 635, 70);  //用绿色的填充颜色去覆盖之前的步数
	//由于字符输出只能是10以内的字符，所以超过10需要进行如下操作
	if (step2 < 10)
	{
		outtextxy(600, 42, '0' + step2);    //打印出AI的步数
	}
	if (step2 >= 10)
	{
		outtextxy(594, 42, '0' + step2 / 10);     //打印出AI的步数的十位数
		outtextxy(606, 42, '0' + step2 % 10);     //打印出AI的步数的个位数
	}
}

//AI下棋二
void AIplaychess1()
{
	int x, y;
	//查找属于棋盘中心位置左右是否有棋子，没有电脑就下这
	for (int i = 11;i <= 13;i++)
	{
		for (int j = 12;j <=14;j++)
		{
			if (board1[i][j] == 0)
			{
				setfillcolor(WHITE);
				solidcircle(i * 25, j * 25, 10);
				board1[i][j] = 2;
				return;       //这里遍历有问题的，后面需要解决，把return去掉后检查
			}
		}
	}
	//随机生成棋子
	while (1)
	{
		x = rand() % (16-8+1)+8;     //x方向在8-16之间随机生成棋子
		y = rand() % (17-9+1)+8;     //y方向在9-17之间随机生成棋子
		if (board1[x][y] == 0)
		{
			setfillcolor(WHITE);
			solidcircle(x * 25, y * 25, 10);
			board1[x][y] = 2;
			break;
		}
	}
}


//|||||||||这是连续出现的情况||||||||||||
//判断电脑棋子将要为2时的应对
int judge8()
{
	int i,j;
	for (i = 2;i < 21;i++)
	{
		for (j = 3;j < 22;j++)
		{
			if (board1[i + 1][j + 1] == 2)
			{
				//8个if从句是让电脑下棋在自己棋的周围8个方向
				if (board1[i + 1][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, j * 25, 10);
					board1[i + 1][j] = 2;
					return 1;
				}
				else if (board1[i + 2][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 1) * 25, 10);
					board1[i + 2][j + 1] = 2;
					return 1;
				}
				else if (board1[i + 1][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, j * 25, 10);
					board1[i + 1][j] = 2;
					return 1;
				}
				else if (board1[i + 1][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, (j + 2) * 25, 10);
					board1[i + 1][j + 2] = 2;
					return 1;
				}
				else if (board1[i + 2][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, j * 25, 10);
					board1[i + 2][j] = 2;
					return 1;
				}
				else if (board1[i][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 2) * 25, 10);
					board1[i][j + 2] = 2;
					return 1;
				}
				else if (board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
				else if (board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断电脑棋子将要为3时的应对                 
int judge7()
{
	int i, j;
	//电脑横排棋子将要为3时
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 24;j++)
		{
			//电脑竖排棋子为两个且两旁都没有玩家棋子堵住
			if (board1[i + 1][j] == board1[i + 2][j] && board1[i + 1][j] == 2)
			{
				if (board1[i][j] == board1[i + 3][j] && board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
			}
		}
	}
	//电脑竖排棋子将要为3时
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 21;j++)
		{
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 1] == 2)
			{
				//电脑横排棋子为两个且两旁都没有玩家棋子堵住
				if (board1[i][j] == board1[i][j + 3] && board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
			}
		}
	}
	//判断电脑棋子正斜将要为3时
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 21;j++)
		{
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 1][j + 1] == 2)
			{
				//电脑正斜棋子为两个且两旁都没有玩家棋子堵住
				if (board1[i][j] == board1[i + 3][j + 3] && board1[i + 3][j + 3] == 0)   
				{
					setfillcolor(WHITE);
					solidcircle((i + 3) * 25, (j + 3) * 25, 10);
					board1[i + 3][j + 3] = 2;
					return 1;
				}
			}
		}
	}
	//判断电脑反斜棋子将要为3时
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 21;j++)
		{
			//电脑反斜棋子为两个且两旁都没有玩家棋子堵住
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 3][j + 1] == 2)
			{
				if (board1[i + 4][j] == board1[i + 1][j + 3] && board1[i + 4][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, (j + 3) * 25, 10);
					board1[i + 1][j + 3] = 2;
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断玩家棋子将要为4时的应对（为4后两边棋子都没有电脑棋子堵住）         
int judge3()
{
	int i, j;
	//玩家棋子横排为3时
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			//玩家竖排棋子为3个且两旁都没有电脑棋子堵住
			if (board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 1][j] == 1)
			{
				if (board1[i][j] == board1[i + 4][j] && board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
			}
		}
	}
	//玩家棋子竖排为3时
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 1] == 1)
			{
				//玩家横排棋子为3个且两旁都没有电脑棋子堵住
				if (board1[i][j] == board1[i][j + 4] && board1[i][j] ==0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
			}
		}
	}
	//玩家棋子正斜为3时
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			//玩家正斜棋子为3个且两旁都没有电脑棋子堵住
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 1][j + 1] == 1)
			{
				if (board1[i][j] == board1[i + 4][j + 4] && board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;					
					return 1;
				}
			}
		}
	}
	//玩家棋子反斜为3时
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 2][j + 2] == 1)
			{
				//玩家反斜棋子为3个且两旁都没有电脑棋子堵住
				if (board1[i + 4][j] == board1[i][j + 4] && board1[i + 4][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 4) * 25, j * 25, 10);
					board1[i + 4][j] = 2;				
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断电脑和玩家棋子将要为5时的应对
int judge4()
{
	int i,j;
	int t=0;
	//电脑和玩家棋子横排为4时的应对
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 24;j++)
		{
			t = board1[i + 1][j];
			if (t == board1[i + 1][j] && t == board1[i + 2][j] && t == board1[i + 3][j] && t == board1[i + 4][j] && t != 0)
			{
				//电脑和玩家竖排棋子为4个且只要有一旁没有电脑棋子堵住，就下棋在那
				if (board1[i + 5][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 5) * 25, j * 25, 10);
					board1[i + 5][j] = 2;
					return 1;
				}
				else if (board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
			}
		}
	}
	//电脑和玩家棋子竖排为4时的应对
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 19;j++)
		{ 
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 3] == board1[i][j + 4] && board1[i][j + 1]!=0)
			{
				//电脑和玩家横排棋子为4个且只要有一旁没有电脑棋子堵住，就下棋在那
				if (board1[i][j + 5] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 5) * 25, 10);
					board1[i][j + 5] = 2;					
					return 1;
				}
				else if (board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;					
					return 1;
				}
			}
		}
	}
	//电脑和玩家棋子正斜为4时的应对
	for (i = 2;i < 18;i++)
	{
		for (j = 3;j < 19;j++)
		{
			t = board1[i + 1][j + 1];
			if (t == board1[i + 1][j + 1] && t == board1[i + 2][j + 2] && t == board1[i + 3][j + 3] && t == board1[i + 4][j + 4] && t !=0)
			{
				//电脑和玩家正斜棋子为4个且只要有一旁没有电脑棋子堵住，就下棋在那
				if (board1[i + 5][j + 5] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 5) * 25, (j + 5) * 25, 10);
					board1[i + 5][j + 5] = 2;
					return 1;
				}
				else if (board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
			}
		}
	}
	//电脑和玩家棋子反斜为4时的应对
	for (i = 3;i < 19;i++)
	{
		for (j = 3;j < 19;j++)
		{
			t = board1[i + 3][j + 1];
			if (t == board1[i + 3][j + 1] && t == board1[i + 2][j + 2] && t == board1[i + 1][j + 3] && t == board1[i][j + 4] && t !=0)
			{
				//电脑和玩家反斜棋子为4个且只要有一旁没有电脑棋子堵住，就下棋在那
				if (board1[i - 1][j + 5] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i - 1) * 25, (j + 5) * 25, 10);
					board1[i - 1][j + 5] = 2;	
					return 1;
				}
				else if (board1[i + 4][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 4) * 25, j * 25, 10);
					board1[i + 4][j] = 2;	
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断电脑棋子为将要4时的应对（不管为4后两边之一是否有玩家棋子）  
int judge33()
{
	int i, j;
	//电脑棋子横排为3时
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 1][j] == 2)
			{
				//电脑竖排棋子为3个且只要有一旁没有玩家棋子堵住，就下棋在那
				if (board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
				else if (board1[i + 4][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 4) * 25, j * 25, 10);
					board1[i + 4][j] = 2;
					return 1;
				}
			}
		}
	}
	//电脑棋子竖排为3时
	for (i = 2;i < 23;i++)           
	{
		for (j = 3;j < 20;j++)    
		{ 
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 1] == 2)
			{
				//电脑横排棋子为3个且只要有一旁没有玩家棋子堵住，就下棋在那
				if (board1[i][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;	
					return 1;
				}
				else if (board1[i][j + 4] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 4) * 25, 10);
					board1[i][j + 4] = 2;		
					return 1;
				}
			}
		}
	}
	//电脑棋子正斜为3时
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 1][j + 1] == 2)
			{
				//电脑正斜棋子为3个且只要有一旁没有玩家棋子堵住，就下棋在那
				if (board1[i][j] ==0 )
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, j * 25, 10);
					board1[i][j] = 2;
					return 1;
				}
				else if (board1[i + 4][j + 4] ==0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 4) * 25, (j + 4) * 25, 10);
					board1[i + 4][j + 4] = 2;							
					return 1;
				}
			}
		}
	}
	//电脑棋子反斜为3时
	for (i = 2;i <19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 2][j + 2] == 2)
			{
				//电脑反斜棋子为3个且只要有一旁没有玩家棋子堵住，就下棋在那
				if (board1[i + 4][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 4) * 25, j * 25, 10);
					board1[i + 4][j] = 2;										
					return 1;
				}
				else if (board1[i][j + 4] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 4) * 25, 10);
					board1[i][j + 4] = 2;
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断电脑棋子将要为4（为4后两旁都没有棋子堵住）
int judge9()
{
	int i, j;
	//电脑棋子横排为3时
	for (i = 3;i < 18;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 1][j] == 2)
			{
				//电脑横排棋子将要为4且两旁都没有玩家棋子堵住
				if (board1[i][j] == board1[i + 4][j] && board1[i][j] == 0)
				{
					//这两个if从句是保证下棋后为四个后没有被堵住
					if (board1[i - 1][j] != 1)
					{
						setfillcolor(WHITE);
						solidcircle(i * 25, j * 25, 10);
						board1[i][j] = 2;
						return 1;
					}
					else if (board1[i + 5][j] != 1)
					{
						setfillcolor(WHITE);
						solidcircle((i + 4) * 25, j * 25, 10);
						board1[i + 4][j] = 2;
						return 1;
					}
				}
			}
		}
	}
	//电脑棋子竖排为3时
	for (i = 2;i < 23;i++)
	{
		for (j = 4;j < 19;j++)
		{
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 1] == 2)
			{
				//电脑竖排棋子将要为4且两旁都没有玩家棋子堵住
				if (board1[i][j] == board1[i][j + 4] && board1[i][j] == 0)
				{
					//这两个if从句是保证下棋后为四个后没有被堵住
					if (board1[i][j - 1] != 1)
					{
						setfillcolor(WHITE);
						solidcircle(i * 25, j * 25, 10);
						board1[i][j] = 2;
						return 1;
					}
					else if (board1[i][j + 5] != 1)
					{
						setfillcolor(WHITE);
						solidcircle(i * 25, (j + 4) * 25, 10);
						board1[i][j + 4] = 2;
						return 1;
					}
				}
			}
		}
	}
	//电脑棋子正斜为3时
	for (i = 3;i < 18;i++)
	{
		for (j = 4;j < 19;j++)
		{
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 1][j + 1] == 2)
			{
				//电脑正斜棋子将要为4且两旁都没有玩家棋子堵住
				if (board1[i][j] == board1[i + 4][j + 4] && board1[i][j] == 0)
				{
					//这两个if从句是保证下棋后为四个后没有被堵住
					if (board1[i - 1][j - 1] != 1)
					{
						setfillcolor(WHITE);
						solidcircle(i * 25, j * 25, 10);
						board1[i][j] = 2;
						return 1;
					}
					else if (board1[i + 5][j + 5] != 1)
					{
						setfillcolor(WHITE);
						solidcircle((i + 4) * 25, (j + 4) * 25, 10);
						board1[i + 4][j + 4] = 2;
						return 1;
					}
				}
			}
		}
	}
	//电脑棋子反斜为3时
	for (i = 3;i < 18;i++)
	{
		for (j = 4;j < 19;j++)
		{
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 2][j + 2] == 2)
			{
				//电脑反斜棋子将要为4且两旁都没有玩家棋子堵住
				if (board1[i + 4][j] == board1[i][j + 4] && board1[i + 4][j] == 0)
				{
					//这两个if从句是保证下棋后为四个后没有被堵住
					if (board1[i + 5][j - 1] != 1)
					{
						setfillcolor(WHITE);
						solidcircle((i + 4) * 25, j * 25, 10);
						board1[i + 4][j] = 2;
						return 1;
					}
					else if (board1[i - 1][j + 5] != 1)
					{
						setfillcolor(WHITE);
						solidcircle(i * 25, (j + 4) * 25, 10);
						board1[i][j + 4] = 2;
						return 1;
					}
				}
			}
		}
	}
	return 0;
}


//|||||||||这是不连续出现的情况||||||||||||
//判断电脑棋子将要为4时的应对（不管为4后两边之一是否有玩家棋子，能构成四个就下）
int judge5()
{
	int i, j;
	//电脑棋子横排为3时
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 3][j] && board1[i][j] == 2)
			{
				if (board1[i + 2][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, j * 25, 10);
					board1[i + 2][j] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i][j] == 2)
			{
				if (board1[i + 1][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, j * 25, 10);
					board1[i + 1][j] = 2;
					return 1;
				}
			}
		}
	}
	//电脑棋子竖排为3时
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 21;j++)
		{
			//这种不连续的有两种情况，可以为00 0，还可以为0 00
			//因为这种情况电脑玩家都适用，只要出现这种情况，电脑就下中间空位置，所以是!=0，
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 3] && board1[i][j] == 2)
			{
				//这是如果中间是空的，没有棋子
				if ( board1[i][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 2) * 25, 10);
					board1[i][j + 2] = 2;									
					return 1;
				}
			}
			else if (board1[i][j] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j] == 2)
			{
				//这是如果中间是空的，没有棋子
				if (board1[i][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 1) * 25, 10);
					board1[i][j + 1] = 2;					
					return 1;
				}
			}
		}
	}
	//电脑棋子正斜为3时
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 21;j++)
		{
			if (board1[i][j] == board1[i + 1][j + 1] && board1[i + 1][j + 1] == board1[i + 3][j + 3] && board1[i][j] == 2)
			{
				if (board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i][j] == 2)
			{
				if (board1[i + 1][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, (j + 1) * 25, 10);
					board1[i + 1][j + 1] = 2;		
					return 1;
				}
			}
		}
	}
	//电脑棋子反斜为3时
	for (i =2;i < 19;i++)
	{
		for (j = 3;j < 21;j++)
		{
			if (board1[i + 4][j] == board1[i + 3][j + 1] && board1[i + 3][j + 1] == board1[i + 1][j + 3] && board1[i + 4][j] == 2)
			{
				if (board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;		
					return 1;
				}
			}
			else if (board1[i + 4][j] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 4][j] == 2)
			{
				if (board1[i + 3][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 3) * 25, (j + 1) * 25, 10);
					board1[i + 3][j + 1] = 2;					
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断玩家棋子将要为4是的应对（为4后两边棋子都没有电脑棋子堵住）
int judge10()
{
	int i, j;
	//玩家棋子横排为3时
	for (i = 3;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			//以下四个方向均有两种情况，以横排为例，00 0和0 00
			if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 3][j] && board1[i][j] == 1)
			{
				//这是为了确保横排电脑都没有棋子堵住玩家，
				if (board1[i + 2][j] == board1[i - 1][j] && board1[i + 2][j] == board1[i + 4][j] && board1[i + 2][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, j * 25, 10);
					board1[i + 2][j] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i][j] == 1)
			{
				if (board1[i + 1][j] == board1[i - 1][j] && board1[i + 1][j] == board1[i + 4][j] && board1[i + 1][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, j * 25, 10);
					board1[i + 1][j] = 2;
					return 1;
				}
			}
		}
	}
	//玩家棋子竖排为3时
	for (i = 2;i < 23;i++)
	{
		for (j = 4;j < 20;j++)
		{
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 3] && board1[i][j] == 1)
			{
				//这是为了确保竖排电脑都没有棋子堵住玩家，
				if (board1[i][j + 2] == board1[i][j - 1] && board1[i][j + 2] == board1[i][j + 4] && board1[i][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 2) * 25, 10);
					board1[i][j + 2] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j] == 1)
			{
				if (board1[i][j + 1] == board1[i][j - 1] && board1[i][j + 1] == board1[i][j + 4] && board1[i][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 1) * 25, 10);
					board1[i][j + 1] = 2;
					return 1;
				}
			}
		}
	}
	//玩家棋子正斜为3时
	for (i = 3;i < 19;i++)
	{
		for (j = 4;j < 20;j++)
		{
			if (board1[i][j] == board1[i + 1][j + 1] && board1[i + 1][j + 1] == board1[i + 3][j + 3] && board1[i][j] == 1)
			{
				//这是为了确保正斜电脑都没有棋子堵住玩家，
				if (board1[i + 2][j + 2] == board1[i - 1][j - 1] && board1[i + 2][j + 2] == board1[i + 4][j + 4] && board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i][j] == 1)
			{
				if (board1[i + 1][j + 1] == board1[i - 1][j - 1] && board1[i + 1][j + 1] == board1[i + 4][j + 4] && board1[i + 1][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, (j + 1) * 25, 10);
					board1[i + 1][j + 1] = 2;
					return 1;
				}
			}
		}
	}
	//玩家棋子反斜为3时
	for (i = 2;i < 18;i++)
	{
		for (j = 4;j < 20;j++)
		{
			if (board1[i + 4][j] == board1[i + 3][j + 1] && board1[i + 3][j + 1] == board1[i + 1][j + 3] && board1[i + 4][j] == 1)
			{
				//这是为了确保反斜电脑都没有棋子堵住玩家，
				if (board1[i + 2][j + 2] == board1[i + 5][j - 1] && board1[i + 2][j + 2] == board1[i][j + 4] && board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;
					return 1;
				}
			}
			else if (board1[i + 4][j] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 4][j] == 1)
			{
				if (board1[i + 3][j + 1] == board1[i + 5][j - 1] && board1[i + 3][j + 1] == board1[i][j + 4] && board1[i + 3][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 3) * 25, (j + 1) * 25, 10);
					board1[i + 3][j + 1] = 2;
					return 1;
				}
			}
		}
	}
	return 0;
}

//判断电脑和玩家棋子将要为5时的应对
int judge6()                    
{
	int i, j;
	int t = 0;
	//电脑和玩家棋子横排为4时的应对
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 4][j] && board1[i][j] != 0)
			{
				if (board1[i + 3][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 3) * 25, j * 25, 10);
					board1[i + 3][j] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 3][j] == board1[i + 4][j] && board1[i][j] != 0)
			{
				if (board1[i + 1][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, j * 25, 10);
					board1[i + 1][j] = 2;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 3][j] && board1[i + 3][j] == board1[i + 4][j] && board1[i][j] != 0)
			{
				if (board1[i + 2][j] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, j * 25, 10);
					board1[i + 2][j] = 2;
					return 1;
				}
			}
		}
	}
	//电脑和玩家棋子竖排为4时的应对
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			//这种不连续的有两种情况，可以为00 00，还可以为00 00，还有00 00，
			//因为这种情况电脑和玩家都适用，只要出现这种情况，电脑就下中间空位置，所以是!=0，
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 4] && board1[i][j] != 0)
			{
				if (board1[i][j + 3] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 3) * 25, 10);
					board1[i][j + 3] = 2;
					flag1++;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 3] == board1[i][j + 4] && board1[i][j] != 0)
			{
				if (board1[i][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 1) * 25, 10);
					board1[i][j + 1] = 2;
					flag1++;
					return 1;
				}
			}
			else if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 3] && board1[i][j + 3] == board1[i][j + 4] && board1[i][j] != 0)
			{
				if (board1[i][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle(i * 25, (j + 2) * 25, 10);
					board1[i][j + 2] = 2;
					flag1++;
					return 1;
				}
			}
		}
	}
	//电脑和玩家棋子正斜为4时的应对
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			t = board1[i][j];
			if (t == board1[i + 1][j + 1] && t == board1[i + 2][j + 2]  && t == board1[i + 4][j + 4] && t != 0)
			{
				if (board1[i + 3][j + 3] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 3) * 25, (j + 3) * 25, 10);
					board1[i + 3][j + 3] = 2;					
					return 1;
				}
			}
			else if (t == board1[i + 2][j + 2] && t == board1[i + 3][j + 3] && t == board1[i + 4][j + 4] && t != 0)
			{
				if (board1[i + 1][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, (j + 1) * 25, 10);
					board1[i + 1][j + 1] = 2;					
					return 1;
				}
			}
			else if (t == board1[i + 1][j + 1] && t == board1[i + 3][j + 3] && t == board1[i + 4][j + 4] && t != 0)
			{
				if (board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;
					return 1;
				}
			}
		}
	}
	//电脑和玩家棋子反斜为4时的应对
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)      
		{
			t = board1[i + 4][j];
			if (t == board1[i + 3][j + 1] && t == board1[i + 2][j + 2] && t == board1[i][j + 4] && t != 0)
			{
				if (board1[i + 1][j + 3] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 1) * 25, (j + 3) * 25, 10);
					board1[i + 1][j + 3] = 2;			
					return 1;
				}
			}
			else if (t == board1[i + 2][j + 2] && t == board1[i + 1][j + 3] && t == board1[i][j + 4] && t != 0)
			{
				if (board1[i + 3][j + 1] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 3) * 25, (j + 1) * 25, 10);
					board1[i + 3][j + 1] = 2;				
					return 1;
				}
			}
			else if (t == board1[i + 3][j] && t == board1[i + 1][j + 3] && t == board1[i][j + 4] && t != 0)
			{
				if (board1[i + 2][j + 2] == 0)
				{
					setfillcolor(WHITE);
					solidcircle((i + 2) * 25, (j + 2) * 25, 10);
					board1[i + 2][j + 2] = 2;
					return 1;
				}
			}
		}
	}
	return 0;
}



//判断游戏输赢
int judge1()
{
	int i, j;
	//横排判断是否已经有五子了
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 3][j] == board1[i + 4][j] && board1[i][j] != 0)
				return 1;
		}
	}
	//竖排判断是否已经有五子了
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 3] == board1[i][j + 4] && board1[i][j] != 0)
				return 1;
		}
	}
	//正斜判断是否已经有五子了
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j] == board1[i + 1][j + 1] && board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 3][j + 3] == board1[i + 4][j + 4] && board1[i][j] != 0)
				return 1;
		}
	}
	//反斜判断是否已经有五子了
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 4][j] == board1[i + 3][j + 1] && board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 1][j + 3] == board1[i][j + 4] && board1[i + 4][j] != 0)
				return 1;
		}
	}
	return 0;
}