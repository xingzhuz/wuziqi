#include "game.h"

int count11 = 0;       //记录玩家的胜负状况
int count22 = 0;       //记录AI的胜负状况
int step11 = 0;        //记录玩家走了的步数
int step22 = 0;        //记录AI走了的步数
int k = -1;           //作为双人对战存储下棋次数的变量
int flag = 0;         //表示下棋的次数 
                      //flag为偶数表示电脑刚下完棋
                      //flag为奇数表示玩家刚下完棋

int board[23][24] = { 0 };      //0表示没有棋子状态
							   //1表示这里有玩家的棋子
							   //2表示这里有电脑的棋子

int judge();    //判断输赢


void initGame()    //初始化游戏
{
	//绘图环境
	initgraph(670, 650);      //图形窗口大小为600x500
	//贴图
	loadimage(NULL, "chess.jpg");
	//BGM();
	setlinecolor(BLACK);        //画的棋盘线为蓝色
	//绘制棋盘
	//画线
	for (int i = 25;i <= 525;i += 25)
	{
		line(i + 25, 75, i + 25, 575);
		line(50, i + 50, 550, i + 50);
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
	settextstyle(18, 0, "黑体");                 //棋盘右边文字的大小及样式
	outtextxy(565, 150, "玩家1:黑棋");            //在棋盘右边打印出电脑所执棋颜色
	fillroundrect(560, 240, 660, 280, 10, 10);   //画圆角矩形
	outtextxy(565, 250, "玩家2:白棋");            //在棋盘右边打印出玩家所执棋颜色

	settextstyle(35, 0, "楷体");                 //打印出棋盘右边VS这个字符串的大小，样式
	settextcolor(RED);                          //打印出棋盘右边VS为红色
	outtextxy(590, 192, "VS");                   //打印出VS这个字符串


	//在棋盘顶上打印的文字
	settextstyle(27, 0, "楷体");               //在棋盘顶上的文字的大小及样式
	settextcolor(BLACK);                       //在棋盘顶上的文字的颜色为黑色
	setfillcolor(GREEN);
	outtextxy(25, 10, "玩家1：黑棋");
	outtextxy(40, 40, "步数：");
	fillrectangle(125, 40, 175, 70);          //画的矩形框
	outtextxy(143, 42, '0' + 0);              //初始的玩家1步数为0                                 
	outtextxy(490, 10, "玩家2：白棋");        //用字符‘0’+数字转换为数字字符进而进行输出，这样可以输出变化的数字
	outtextxy(505, 40, "步数：");
	fillrectangle(590, 40, 645, 70);          //画的矩形框
	outtextxy(608, 42, '0' + 0);              //初始的玩家2步数为0

	//在棋盘顶上打印胜负状况
	outtextxy(260, 10, "玩家1:");
	outtextxy(335, 10, " 玩家2");
	//由于字符只能输出10以内字符，所以需要进行如下操作
	//这是如果玩家1胜场数超过10后的处理
	if (count11 < 10)
	{
		outtextxy(290, 40, '0' + count11);    //打印出玩家1的胜场数
	}
	if (count11 >= 10)
	{
		outtextxy(280, 40, '0' + count11 / 10);    //打印出玩家1的胜场数的十位数
		outtextxy(295, 40, '0' + count11 % 10);    //打印出玩家1的胜场数的各位数
	}
	//这是玩家2胜场数超过10后的处理
	if (count22 < 10)
	{
		outtextxy(330, 40, ":");
		outtextxy(370, 40, '0' + count22);    //打印出玩家2的胜场数
	}
	if (count22 >= 10)
	{
		outtextxy(330, 40, ":");
		outtextxy(366, 40, '0' + count22 / 10);    //打印出玩家2的胜场数的十位数
		outtextxy(380, 40, '0' + count22 % 10);    //打印出玩家2的胜场数的个位数
	}

	//棋盘底部的文字，表示玩家可以进行的操作
	setfillcolor(YELLOW);              //矩形框的填空颜色
	settextstyle(23, 0, NULL);           //矩形框内文字的大小及样式
	fillrectangle(35, 600, 140, 630);    //画的几个矩形框
	fillrectangle(535, 600, 640, 630);
	fillrectangle(260, 600, 415, 630);
	outtextxy(40, 605, "重新开始");      //矩形框内的文字
	outtextxy(540, 605, "退出游戏");
	outtextxy(265, 605, "退出双人对战");

	//棋盘右下角的文字，表示该谁下棋
	//这里先进行打印是为了后面直接用背景色覆盖即可，直接放在鼠标点击函数里会闪烁
	setfillcolor(WHITE);                 //打印该谁棋子的矩形框的填充颜色为白色
	fillrectangle(570, 350, 620, 530);   //画的矩形框
	settextstyle(30, 0, NULL);           //打印的该谁下棋文字的大小及样式
	outtextxy(580, 360, "黑");
	outtextxy(580, 400, "棋");
	outtextxy(580, 440, "下");
	outtextxy(580, 480, "棋");
}

//下棋
void playChess()
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
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)  //绝对值
				{
					a = i;
					b = j;
				}
			}
		}
		
		//鼠标左键按下
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			setbkcolor(WHITE);     //打印黑棋下棋的矩形框的填充颜色为白色

			//这是为了让玩家清楚知道此时该谁下棋了
			if (flag % 2 == 0)    //如果flag为偶数，说明该白棋下棋了
			{
				clearrectangle(570, 350, 620, 530);
				outtextxy(580, 360, "白");
				outtextxy(580, 400, "棋");
				outtextxy(580, 440, "下");
				outtextxy(580, 480, "棋");
				
			}
			else                  //如果flag为奇数，说明该黑棋下棋了
			{
				clearrectangle(570, 350, 620, 530);
				outtextxy(580, 360, "黑");
				outtextxy(580, 400, "棋");
				outtextxy(580, 440, "下");
				outtextxy(580, 480, "棋");
			}
			//判断玩家是否需要进行重新开始、退出AI对战、退出游戏操作
			if (m.x > 35 && m.x < 140 && m.y>600 && m.y < 630)        //这是重新开始AI对战的矩形范围
			{
				//这个for循环操作是为了能够把全局变量数组重新置为0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board[i][j] = 0;
					}
				}
				step11 = 0, step22 = 0;    //之前记录的步数把它赋值为0
				player();                 //再次进入双人对战
			}
			if (m.x > 535 && m.x < 640 && m.y>600 && m.y < 630)    //这是退出游戏的矩形框范围
			{
				exit(0);  //退出游戏
			}
			if (m.x > 260 && m.x < 415 && m.y>600 && m.y < 630)    //这是退出AI对战的矩形框范围
			{
				//这个for循环操作是为了能够把全局变量数组重新置为0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board[i][j] = 0;
					}
				}
				step11 = 0, step22 = 0;         //之前记录的步数把它赋值为0
				count11 = 0, count22 = 0;        //之前记录的胜负状况全把它赋值为0
				break;                          //退出这个循环，为了结束这个双人对战，重新进入main()函数
			}
			//重叠
			if (board[a][b] != 0)
			{
				MessageBox(NULL, "这里已经有棋子了，请重新选择", "提示", MB_OK);
				continue;   //退出循环重新进入
			}
			if (flag % 2 == 0)      //偶数，即玩家1下棋
			{
				setfillcolor(BLACK);
				solidcircle(a * 25, b * 25, 10);
				board[a][b] = 1;

				//打印玩家1步数
				step11++;                           //玩家1步数加一
				setbkcolor(GREEN);                    //背景颜色为绿色
				clearrectangle(125, 40, 175, 70);     //用填充颜色覆盖之前的步数
				//由于字符输出只能是10以内的字符，所以超过10需要进行如下操作
				if (step11 < 10)
				{
					outtextxy(143, 42, '0' + step11);    //打印出玩家1的步数
				}
				if (step11 >= 10)
				{
					outtextxy(136, 42, '0' + step11 / 10);    //打印出玩家1的步数的十位数
					outtextxy(150, 42, '0' + step11 % 10);    //打印出玩家1的步数的个位数
				}
			}
			else       //奇数，即玩家2下棋
			{
				setfillcolor(WHITE);
				solidcircle(a * 25, b * 25, 10);
				board[a][b] = 2;

				//打印玩家2步数
				step22++;                           //玩家2步数加一
				setbkcolor(GREEN);                   //背景颜色为绿色
				clearrectangle(590, 40, 645, 70);    //用填充颜色覆盖之前的步数
				//由于字符输出只能是10以内的字符，所以超过10需要进行如下操作
				if (step22 < 10)
				{
					outtextxy(608, 42, '0' + step22);         //打印出玩家2的步数
				}
				if (step22 >= 10)
				{
					outtextxy(601, 42, '0' + step22 / 10);    //打印出玩家2的步数的十位数
					outtextxy(615, 42, '0' + step22 % 10);    //打印出玩家2的步数的个位数

				}
			}
			flag++;
		}
		if (judge())
		{
			if (flag % 2 == 0)
			{
				count22++;                 //玩家2赢了，将储存胜场数的变量加一
				k = load_count();           //把储存下棋次数的文件夹打开，把值赋给k
				save_count(k);             //储存这一次的下棋次数进入save_count函数中AI.dat文件里
				save_record(flag);        //把这一次双人对战的战绩存入文件AI.txt中

				//判断玩家是否需要继续双人对战
				int isok = MessageBox(NULL, "玩家2胜利，是否需要继续双人对战", "游戏结束", MB_OKCANCEL);
				if (isok == IDOK)
				{
					//这个for循环操作是为了能够把全局变量数组重新置为0
					for (int i = 2;i < 23;i++)
					{
						for (int j = 3;j < 24;j++)
						{
							board[i][j] = 0;
						}
					}
					step11 = 0, step22 = 0;         //之前记录的步数把它赋值为0
					player();                 //再次进入双人对战
				}
				else if (isok == IDCANCEL)
				{
					exit(0);     //退出游戏
				}
			}
			else
			{
				count11++;               //玩家1赢了，将储存胜场数的变量加一
				k = load_count();           //把储存下棋次数的文件夹打开，把值赋给k
				save_count(k);             //储存这一次的下棋次数进入save_count函数中AI.dat文件里
				save_record(flag);        //把这一次双人对战的战绩存入文件AI.txt中

				//判断玩家是否需要继续双人对战
				int isok1 = MessageBox(NULL, "玩家1胜利，是否需要继续双人对战", "游戏结束", MB_OKCANCEL);
				if (isok1 == IDOK)
				{
					//这个for循环操作是为了能够把全局变量数组重新置为0
					for (int i = 2;i < 23;i++)
					{
						for (int j = 3;j < 24;j++)
						{
							board[i][j] = 0;
						}
					}
					step11 = 0, step22 = 0;        //之前记录的步数把它赋值为0
					player();                 //再次进入双人对战
				}
				else if (isok1 == IDCANCEL)
				{
					exit(0);    //退出游戏
				}
			}
		}
	}
}

//判断游戏输赢
int judge()
{
	int i, j;
	//横排判断是否已经有五子了
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i + 3][j] == board[i + 4][j] && board[i][j] != 0)
				return 1;
		}
	}
	//竖排判断是否已经有五子了
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j + 3] == board[i][j + 4] && board[i][j] != 0)
				return 1;
		}
	}
	//正斜判断是否已经有五子了
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i + 3][j + 3] == board[i + 4][j + 4] && board[i][j] != 0)
				return 1;
		}
	}
	//反斜判断是否已经有五子了
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board[i + 4][j] == board[i + 3][j + 1] && board[i + 3][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 1][j + 3] && board[i + 1][j + 3] == board[i][j + 4] && board[i + 4][j] != 0)
				return 1;
		}
	}
	return 0;
}


int player()
{ 
	initGame();    //进入棋盘初始化
	while (1)
	{
		playChess();   //进入正式下棋
		break;
	}
	
	return 0;
}