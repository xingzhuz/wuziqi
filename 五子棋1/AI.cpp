#include "game.h"

int count1 = 0;       //��¼��ҵ�ʤ��״��
int count2 = 0;       //��¼AI��ʤ��״��
int step1 = 0;        //��¼������˵Ĳ���
int step2 = 0;        //��¼AI���˵Ĳ���
int j = -1;           //��Ϊ��AI��ս�洢��������ı���
int flag1 = 0;              //��ʾ����Ĵ��� 
                             //flagΪż����ʾ���Ը�������
                             //flagΪ������ʾ��Ҹ�������

int board1[23][24] = { 0 };  //0��ʾû������״̬
                             //1��ʾ��������ҵ�����
                             //2��ʾ�����е��Ե�����

HWND hwnd;
//AI��ս��������
void AI()
{
	initGame1();   //�����ʼ����Ϸ
	while (1)
	{
		playerplaychess();   //����AI����������
		break;
	}
}

//��ʼ����Ϸ
void initGame1()
{
	
	//��ͼ����
	hwnd=initgraph(670, 650);      //ͼ�δ��ڴ�СΪ600x500
	//��ͼ
	loadimage(NULL, "chess.jpg");
	//BGM();
	setlinecolor(BLACK);        //����������Ϊ��ɫ
	//��������
	//����
	for (int i = 25;i <= 525;i += 25)
	{
		line(i+25, 75, i+25, 575);
		line(50, i+50, 550, i+50);
	}

	//�����������ӡ�����ɫС��С��
	setfillcolor(BLACK);             //�����ϻ���С��������ɫ
	solidcircle((10 + 2) * 25, (10 + 3) * 25, 5);
	solidcircle((6 + 2) * 25, (14 + 3) * 25, 5);
	solidcircle((14 + 2) * 25, (14 + 3) * 25, 5);
	solidcircle((6 + 2) * 25, (6 + 3) * 25, 5);
	solidcircle((14 + 2) * 25, (6 + 3) * 25, 5);

	//�����ұ��ַ����Ĳ���
	setbkmode(TRANSPARENT);            //������ַ�������Ϊ͸��
	setfillcolor(LIGHTGRAY);          //Բ�Ǿ��ε������ɫ
	fillroundrect(560, 140, 660, 180, 10, 10);    //��Բ�Ǿ���
	settextcolor(BLACK);                         //��ӡ�������ұߵ����ֵ���ɫ
	settextstyle(20, 0, "����");                 //�����ұ����ֵĴ�С����ʽ
	outtextxy(565, 150, "���:����");            //�������ұߴ�ӡ��������ִ����ɫ
	fillroundrect(560, 240, 660, 280, 10, 10);   //��Բ�Ǿ���
	outtextxy(565, 250, "���:����");            //�������ұߴ�ӡ�������ִ����ɫ

	settextstyle(35, 0, "����");                 //��ӡ�������ұ�VS����ַ����Ĵ�С����ʽ
	settextcolor(RED);                          //��ӡ�������ұ�VSΪ��ɫ
	outtextxy(590, 192, "VS");                   //��ӡ��VS����ַ���
	

	//�����̶��ϴ�ӡ������
	settextstyle(27, 0, "����");                 //�����̶��ϵ����ֵĴ�С����ʽ
	settextcolor(BLACK);                         //�����̶��ϵ����ֵ���ɫΪ��ɫ
	setfillcolor(GREEN);                         //�����̶��ϻ��ľ��ο�������ɫΪ��ɫ
	outtextxy(45, 10, "���ԣ�����");             
	outtextxy(45, 40, "������");
	fillrectangle(130, 40, 180, 70);            //���ľ��ξ��ο�
	outtextxy(148, 42, '0' + 0);                //���ַ���0��+����ת��Ϊ�����ַ��������������������������仯������
	outtextxy(520, 10, "AI������");
	outtextxy(500, 40, "������");
	fillrectangle(580, 40, 635, 70);            //���ľ��ο�
	outtextxy(600, 42, '0' + 0);
	
	//�����̶��ϴ�ӡʤ��״��
	outtextxy(280, 10, "���:");
	outtextxy(355, 10, " AI");
	//�����ַ�ֻ�����10�����ַ���������Ҫ�������²���
	//����������ʤ��������10��Ĵ���
	if (count1 < 10)
	{
		outtextxy(300, 40, '0' + count1);    //��ӡ����ҵ�ʤ����
	}
	if (count1 >= 10)
	{
		outtextxy(292, 40, '0' + count1 / 10);    //��ӡ����ҵ�ʤ������ʮλ��
		outtextxy(306, 40, '0' + count1 % 10);    //��ӡ����ҵ�ʤ�����ĸ�λ��
	}
	//���ǵ���ʤ��������10��Ĵ���
	if (count2 < 10)
	{
		outtextxy(336, 40, ":");        
		outtextxy(370, 40, '0' + count2);        //��ӡ��AI��ʤ����
	}
	if (count2 >= 10)
	{
		outtextxy(336, 40, ":");
		outtextxy(366, 40, '0' + count2 / 10);    //��ӡ��AI��ʤ������ʮλ��
		outtextxy(380, 40, '0' + count2 % 10);    //��ӡ��AI��ʤ�����ĸ�λ��
	}

	//���̵ײ������֣���ʾ��ҿ��Խ��еĲ���
	setfillcolor(YELLOW);              //���ο�������ɫ
	settextstyle(23,0, NULL);           //���ο������ֵĴ�С����ʽ
	fillrectangle(35, 600, 140, 630);    //���ļ������ο�
	fillrectangle(535, 600, 640, 630);
	fillrectangle(265, 600, 395, 630);
	outtextxy(40, 605, "���¿�ʼ");      //���ο��ڵ�����
	outtextxy(540, 605, "�˳���Ϸ");
	outtextxy(270, 605, "�˳�AI��ս");
}


//�������
void playerplaychess()
{
	int a = 0, b = 0;
	//���
	MOUSEMSG m;     //���������Ϣ
	while (1)
	{
		m = GetMouseMsg();    //��ȡһ�������Ϣ
		
		//��ֹ���������Ӿ����ģ����������߸��ӽ��ߴ�
		for (int i = 2;i < 23;i++)
		{
			for (int j = 3;j < 24;j++)
			{
				//�Ӹ�abs���������ֵ��ʹ��ÿ��ֻ��Ҫ������ߴ��Ա߷�Χ���ɣ����ܹ����ڽ��ߴ�
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)
				{
					a = i;
					b = j;
				}
			}
		}
		//�������
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//�ж�����Ƿ���Ҫ�������¿�ʼ���˳�AI��ս���˳���Ϸ����
			if (m.x > 35 && m.x < 140 && m.y>600 && m.y < 630)     //�������¿�ʼAI��ս�ľ��η�Χ
			{
				//���forѭ����Ϊ�˽�ȫ�ֱ��������ʼ��Ϊ0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board1[i][j] = 0;
					}
				}
				step1 = 0, step2 = 0;       //֮ǰ��¼�Ĳ���������ֵΪ0
				AI();    //�ٴν���AI��ս
			}
			if (m.x > 535 && m.x < 640 && m.y>600 && m.y < 630)    //�����˳���Ϸ�ľ��ο�Χ
			{
				exit(0);  //�˳���Ϸ
			}
			if (m.x > 265 && m.x < 395 && m.y>600 && m.y < 630)    //�����˳�AI��ս�ľ��ο�Χ
			{
				//���forѭ����Ϊ�˽�ȫ�ֱ��������ʼ��Ϊ0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board1[i][j] = 0;
					}
				}
				step1 = 0, step2 = 0;      //֮ǰ��¼�Ĳ���������ֵΪ0
				count1 = 0, count2 = 0;   //֮ǰ��¼��ʤ��״��ȫ������ֵΪ0
				break;         //�˳����ѭ����Ϊ�˽������AI��ս�����½���main()����
			}

			//��������ص��˵���ʾ����
			if (board1[a][b] != 0)
			{
				MessageBox(hwnd, "�����Ѿ��������ˣ�������ѡ��", "��ʾ", MB_OK);
				continue;   //�˳�ѭ�����½���
			}
			if (flag1 % 2 == 0)      //ż��
			{
				setfillcolor(BLACK);
				solidcircle(a * 25, b * 25, 10);
				board1[a][b] = 1;
			}
			step1++;    //��Ҳ�����һ
			flag1++;   

			//��ӡ��ҵĲ���
			setbkcolor(GREEN);     //������ɫΪ��ɫ
			clearrectangle(130, 40, 180, 70);       //�������ɫ����֮ǰ�Ĳ���
			//�����ַ����ֻ����10���ڵ��ַ������Գ���10��Ҫ�������²���
			if (step1 < 10)
			{
				outtextxy(148, 42, '0' + step1);    //��ӡ����ҵĲ���
			}
			if (step1 >= 10)
			{
				outtextxy(142, 42, '0' + step1 / 10);    //��ӡ����ҵĲ�����ʮλ��
				outtextxy(154, 42, '0' + step1 % 10);    //��ӡ����ҵĲ����ĸ�λ��
			}

			//�жϴ�ʱ����Ӯ
			if (judge1() == 1)
			{
				if (flag1 % 2 == 1)
				{
					count1++;               //���Ӯ�ˣ���¼���ı�����һ 
					j = load_count();       //�Ѵ�������������ļ��д򿪣���ֵ����j
					save_count(j);          //������һ�ε������������save_count������AI.dat�ļ���
					save_record(flag1);     //����һ��AI��ս��ս�������ļ�AI.txt��

					//�ж�����Ƿ���Ҫ����AI��ս
					int isok = MessageBox(hwnd, "���ʤ��,�Ƿ����AI��ս", "��Ϸ����", MB_OKCANCEL);
					if (isok == IDOK)
					{
						//���forѭ����Ϊ�˽�ȫ�ֱ��������ʼ��Ϊ0
						for (int i = 2;i < 23;i++)
						{
							for (int j = 3;j < 24;j++)
							{
								board1[i][j] = 0;
							}
						}
						step1 = 0, step2 = 0;    //֮ǰ��¼�Ĳ���������ֵΪ0
						AI();       //�ٴν���AI��ս
					}
					else if (isok == IDCANCEL)
					{
						exit(0);    //�˳���Ϸ
					}
				}
				
			}

			AIplaychess();       //AI����
			//�жϴ�ʱ����Ӯ
			if (judge1() == 1)
			{
				if (flag1 % 2 == 0)
				{
					count2++;                 //AIӮ�ˣ���¼���ı�����һ 
					j = load_count();         //�Ѵ�������������ļ��д򿪣���ֵ����j
					save_count(j);            //������һ�ε������������save_count������AI.dat�ļ���
					save_record(flag1);       //����һ��AI��ս��ս�������ļ�AI.txt��

					//�ж�����Ƿ���Ҫ����AI��ս
					int isok1 = MessageBox(hwnd, "����ʤ�����Ƿ����AI��ս", "��Ϸ����", MB_OKCANCEL);
					if (isok1 == IDOK)
					{
						//���forѭ����Ϊ�˰�ȫ�ֱ��������ʼ��Ϊ0
						for (int i = 2;i < 23;i++)
						{
							for (int j = 3;j < 24;j++)
							{
								board1[i][j] = 0;
							}
						}
						step1 = 0, step2 = 0;    //֮ǰ��¼�Ĳ���������ֵΪ0
						AI();                //�ٴν���AI��ս
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

//AI����һ
void AIplaychess()
{
	int a,b,c,d,e,f,g,h,i,j;
	a = judge4();      //����������жϵ��Ժ�������ӽ�ҪΪ5ʱ��Ӧ��
	if (a == 0)
	{ 
		f = judge6();    //������������жϵ��Ժ�������ӽ�ҪΪ5ʱ��Ӧ��
		if (f == 0)
		{
			i = judge9();   //����������жϵ������ӽ�ҪΪ4��Ϊ4�����Զ�û�����Ӷ�ס��
			if (i == 0)
			{
				j = judge10();   //������������ж�������ӽ�ҪΪ4ʱ��Ӧ�ԣ�Ϊ4���������Ӷ�û�е������Ӷ�ס��
				if (j == 0)
				{                             
					e = judge3();    //����������ж�������ӽ�ҪΪ4ʱ��Ӧ�ԣ�Ϊ4���������Ӷ�û�е������Ӷ�ס�� 
					if (e == 0)
					{
						b = judge5();   //������������жϵ������ӽ�ҪΪ4ʱ��Ӧ�ԣ�����Ϊ4������֮һ�Ƿ���������ӣ�         
						if (b == 0)
						{
							c = judge33();     //����������жϵ�������Ϊ��Ҫ4ʱ��Ӧ�ԣ�����Ϊ4������֮һ�Ƿ���������ӣ�  
							if (c == 0)
							{
								g = judge7();       //����������жϵ������ӽ�ҪΪ3ʱ��Ӧ��
								if (g == 0)
								{
									h = judge8();      //����������жϵ������ӽ�ҪΪ2ʱ��Ӧ��
									if (h == 0)
									{
										AIplaychess1();   //AI�����
									}
								}
							}
						}
					}
				}
			}
		}
	}
	flag1++;   //AI�������flag1++
	step2++;   //AI������󣬲���step1++

	//��ӡAI�Ĳ���
	setbkcolor(GREEN);      //�������ο�������ɫ
	clearrectangle(580, 40, 635, 70);  //����ɫ�������ɫȥ����֮ǰ�Ĳ���
	//�����ַ����ֻ����10���ڵ��ַ������Գ���10��Ҫ�������²���
	if (step2 < 10)
	{
		outtextxy(600, 42, '0' + step2);    //��ӡ��AI�Ĳ���
	}
	if (step2 >= 10)
	{
		outtextxy(594, 42, '0' + step2 / 10);     //��ӡ��AI�Ĳ�����ʮλ��
		outtextxy(606, 42, '0' + step2 % 10);     //��ӡ��AI�Ĳ����ĸ�λ��
	}
}

//AI�����
void AIplaychess1()
{
	int x, y;
	//����������������λ�������Ƿ������ӣ�û�е��Ծ�����
	for (int i = 11;i <= 13;i++)
	{
		for (int j = 12;j <=14;j++)
		{
			if (board1[i][j] == 0)
			{
				setfillcolor(WHITE);
				solidcircle(i * 25, j * 25, 10);
				board1[i][j] = 2;
				return;       //�������������ģ�������Ҫ�������returnȥ������
			}
		}
	}
	//�����������
	while (1)
	{
		x = rand() % (16-8+1)+8;     //x������8-16֮�������������
		y = rand() % (17-9+1)+8;     //y������9-17֮�������������
		if (board1[x][y] == 0)
		{
			setfillcolor(WHITE);
			solidcircle(x * 25, y * 25, 10);
			board1[x][y] = 2;
			break;
		}
	}
}


//|||||||||�����������ֵ����||||||||||||
//�жϵ������ӽ�ҪΪ2ʱ��Ӧ��
int judge8()
{
	int i,j;
	for (i = 2;i < 21;i++)
	{
		for (j = 3;j < 22;j++)
		{
			if (board1[i + 1][j + 1] == 2)
			{
				//8��if�Ӿ����õ����������Լ������Χ8������
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

//�жϵ������ӽ�ҪΪ3ʱ��Ӧ��                 
int judge7()
{
	int i, j;
	//���Ժ������ӽ�ҪΪ3ʱ
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 24;j++)
		{
			//������������Ϊ���������Զ�û��������Ӷ�ס
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
	//�����������ӽ�ҪΪ3ʱ
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 21;j++)
		{
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 1] == 2)
			{
				//���Ժ�������Ϊ���������Զ�û��������Ӷ�ס
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
	//�жϵ���������б��ҪΪ3ʱ
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 21;j++)
		{
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 1][j + 1] == 2)
			{
				//������б����Ϊ���������Զ�û��������Ӷ�ס
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
	//�жϵ��Է�б���ӽ�ҪΪ3ʱ
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 21;j++)
		{
			//���Է�б����Ϊ���������Զ�û��������Ӷ�ס
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

//�ж�������ӽ�ҪΪ4ʱ��Ӧ�ԣ�Ϊ4���������Ӷ�û�е������Ӷ�ס��         
int judge3()
{
	int i, j;
	//������Ӻ���Ϊ3ʱ
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			//�����������Ϊ3�������Զ�û�е������Ӷ�ס
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
	//�����������Ϊ3ʱ
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 1] == 1)
			{
				//��Һ�������Ϊ3�������Զ�û�е������Ӷ�ס
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
	//���������бΪ3ʱ
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			//�����б����Ϊ3�������Զ�û�е������Ӷ�ס
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
	//������ӷ�бΪ3ʱ
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 2][j + 2] == 1)
			{
				//��ҷ�б����Ϊ3�������Զ�û�е������Ӷ�ס
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

//�жϵ��Ժ�������ӽ�ҪΪ5ʱ��Ӧ��
int judge4()
{
	int i,j;
	int t=0;
	//���Ժ�������Ӻ���Ϊ4ʱ��Ӧ��
	for (i = 2;i < 20;i++)
	{
		for (j = 3;j < 24;j++)
		{
			t = board1[i + 1][j];
			if (t == board1[i + 1][j] && t == board1[i + 2][j] && t == board1[i + 3][j] && t == board1[i + 4][j] && t != 0)
			{
				//���Ժ������������Ϊ4����ֻҪ��һ��û�е������Ӷ�ס������������
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
	//���Ժ������������Ϊ4ʱ��Ӧ��
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 19;j++)
		{ 
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 3] == board1[i][j + 4] && board1[i][j + 1]!=0)
			{
				//���Ժ���Һ�������Ϊ4����ֻҪ��һ��û�е������Ӷ�ס������������
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
	//���Ժ����������бΪ4ʱ��Ӧ��
	for (i = 2;i < 18;i++)
	{
		for (j = 3;j < 19;j++)
		{
			t = board1[i + 1][j + 1];
			if (t == board1[i + 1][j + 1] && t == board1[i + 2][j + 2] && t == board1[i + 3][j + 3] && t == board1[i + 4][j + 4] && t !=0)
			{
				//���Ժ������б����Ϊ4����ֻҪ��һ��û�е������Ӷ�ס������������
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
	//���Ժ�������ӷ�бΪ4ʱ��Ӧ��
	for (i = 3;i < 19;i++)
	{
		for (j = 3;j < 19;j++)
		{
			t = board1[i + 3][j + 1];
			if (t == board1[i + 3][j + 1] && t == board1[i + 2][j + 2] && t == board1[i + 1][j + 3] && t == board1[i][j + 4] && t !=0)
			{
				//���Ժ���ҷ�б����Ϊ4����ֻҪ��һ��û�е������Ӷ�ס������������
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

//�жϵ�������Ϊ��Ҫ4ʱ��Ӧ�ԣ�����Ϊ4������֮һ�Ƿ���������ӣ�  
int judge33()
{
	int i, j;
	//�������Ӻ���Ϊ3ʱ
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 1][j] == 2)
			{
				//������������Ϊ3����ֻҪ��һ��û��������Ӷ�ס������������
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
	//������������Ϊ3ʱ
	for (i = 2;i < 23;i++)           
	{
		for (j = 3;j < 20;j++)    
		{ 
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 1] == 2)
			{
				//���Ժ�������Ϊ3����ֻҪ��һ��û��������Ӷ�ס������������
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
	//����������бΪ3ʱ
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 1][j + 1] == 2)
			{
				//������б����Ϊ3����ֻҪ��һ��û��������Ӷ�ס������������
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
	//�������ӷ�бΪ3ʱ
	for (i = 2;i <19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 2][j + 2] == 2)
			{
				//���Է�б����Ϊ3����ֻҪ��һ��û��������Ӷ�ס������������
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

//�жϵ������ӽ�ҪΪ4��Ϊ4�����Զ�û�����Ӷ�ס��
int judge9()
{
	int i, j;
	//�������Ӻ���Ϊ3ʱ
	for (i = 3;i < 18;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 1][j] == 2)
			{
				//���Ժ������ӽ�ҪΪ4�����Զ�û��������Ӷ�ס
				if (board1[i][j] == board1[i + 4][j] && board1[i][j] == 0)
				{
					//������if�Ӿ��Ǳ�֤�����Ϊ�ĸ���û�б���ס
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
	//������������Ϊ3ʱ
	for (i = 2;i < 23;i++)
	{
		for (j = 4;j < 19;j++)
		{
			if (board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 1] == 2)
			{
				//�����������ӽ�ҪΪ4�����Զ�û��������Ӷ�ס
				if (board1[i][j] == board1[i][j + 4] && board1[i][j] == 0)
				{
					//������if�Ӿ��Ǳ�֤�����Ϊ�ĸ���û�б���ס
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
	//����������бΪ3ʱ
	for (i = 3;i < 18;i++)
	{
		for (j = 4;j < 19;j++)
		{
			if (board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 1][j + 1] == 2)
			{
				//������б���ӽ�ҪΪ4�����Զ�û��������Ӷ�ס
				if (board1[i][j] == board1[i + 4][j + 4] && board1[i][j] == 0)
				{
					//������if�Ӿ��Ǳ�֤�����Ϊ�ĸ���û�б���ס
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
	//�������ӷ�бΪ3ʱ
	for (i = 3;i < 18;i++)
	{
		for (j = 4;j < 19;j++)
		{
			if (board1[i + 3][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 1][j + 3] && board1[i + 2][j + 2] == 2)
			{
				//���Է�б���ӽ�ҪΪ4�����Զ�û��������Ӷ�ס
				if (board1[i + 4][j] == board1[i][j + 4] && board1[i + 4][j] == 0)
				{
					//������if�Ӿ��Ǳ�֤�����Ϊ�ĸ���û�б���ס
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


//|||||||||���ǲ��������ֵ����||||||||||||
//�жϵ������ӽ�ҪΪ4ʱ��Ӧ�ԣ�����Ϊ4������֮һ�Ƿ���������ӣ��ܹ����ĸ����£�
int judge5()
{
	int i, j;
	//�������Ӻ���Ϊ3ʱ
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
	//������������Ϊ3ʱ
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 21;j++)
		{
			//���ֲ����������������������Ϊ00 0��������Ϊ0 00
			//��Ϊ�������������Ҷ����ã�ֻҪ����������������Ծ����м��λ�ã�������!=0��
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 3] && board1[i][j] == 2)
			{
				//��������м��ǿյģ�û������
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
				//��������м��ǿյģ�û������
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
	//����������бΪ3ʱ
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
	//�������ӷ�бΪ3ʱ
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

//�ж�������ӽ�ҪΪ4�ǵ�Ӧ�ԣ�Ϊ4���������Ӷ�û�е������Ӷ�ס��
int judge10()
{
	int i, j;
	//������Ӻ���Ϊ3ʱ
	for (i = 3;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			//�����ĸ������������������Ժ���Ϊ����00 0��0 00
			if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 3][j] && board1[i][j] == 1)
			{
				//����Ϊ��ȷ�����ŵ��Զ�û�����Ӷ�ס��ң�
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
	//�����������Ϊ3ʱ
	for (i = 2;i < 23;i++)
	{
		for (j = 4;j < 20;j++)
		{
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 3] && board1[i][j] == 1)
			{
				//����Ϊ��ȷ�����ŵ��Զ�û�����Ӷ�ס��ң�
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
	//���������бΪ3ʱ
	for (i = 3;i < 19;i++)
	{
		for (j = 4;j < 20;j++)
		{
			if (board1[i][j] == board1[i + 1][j + 1] && board1[i + 1][j + 1] == board1[i + 3][j + 3] && board1[i][j] == 1)
			{
				//����Ϊ��ȷ����б���Զ�û�����Ӷ�ס��ң�
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
	//������ӷ�бΪ3ʱ
	for (i = 2;i < 18;i++)
	{
		for (j = 4;j < 20;j++)
		{
			if (board1[i + 4][j] == board1[i + 3][j + 1] && board1[i + 3][j + 1] == board1[i + 1][j + 3] && board1[i + 4][j] == 1)
			{
				//����Ϊ��ȷ����б���Զ�û�����Ӷ�ס��ң�
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

//�жϵ��Ժ�������ӽ�ҪΪ5ʱ��Ӧ��
int judge6()                    
{
	int i, j;
	int t = 0;
	//���Ժ�������Ӻ���Ϊ4ʱ��Ӧ��
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
	//���Ժ������������Ϊ4ʱ��Ӧ��
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			//���ֲ����������������������Ϊ00 00��������Ϊ00 00������00 00��
			//��Ϊ����������Ժ���Ҷ����ã�ֻҪ����������������Ծ����м��λ�ã�������!=0��
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
	//���Ժ����������бΪ4ʱ��Ӧ��
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
	//���Ժ�������ӷ�бΪ4ʱ��Ӧ��
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



//�ж���Ϸ��Ӯ
int judge1()
{
	int i, j;
	//�����ж��Ƿ��Ѿ���������
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board1[i][j] == board1[i + 1][j] && board1[i + 1][j] == board1[i + 2][j] && board1[i + 2][j] == board1[i + 3][j] && board1[i + 3][j] == board1[i + 4][j] && board1[i][j] != 0)
				return 1;
		}
	}
	//�����ж��Ƿ��Ѿ���������
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j] == board1[i][j + 1] && board1[i][j + 1] == board1[i][j + 2] && board1[i][j + 2] == board1[i][j + 3] && board1[i][j + 3] == board1[i][j + 4] && board1[i][j] != 0)
				return 1;
		}
	}
	//��б�ж��Ƿ��Ѿ���������
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board1[i][j] == board1[i + 1][j + 1] && board1[i + 1][j + 1] == board1[i + 2][j + 2] && board1[i + 2][j + 2] == board1[i + 3][j + 3] && board1[i + 3][j + 3] == board1[i + 4][j + 4] && board1[i][j] != 0)
				return 1;
		}
	}
	//��б�ж��Ƿ��Ѿ���������
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