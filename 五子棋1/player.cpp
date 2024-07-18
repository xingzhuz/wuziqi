#include "game.h"

int count11 = 0;       //��¼��ҵ�ʤ��״��
int count22 = 0;       //��¼AI��ʤ��״��
int step11 = 0;        //��¼������˵Ĳ���
int step22 = 0;        //��¼AI���˵Ĳ���
int k = -1;           //��Ϊ˫�˶�ս�洢��������ı���
int flag = 0;         //��ʾ����Ĵ��� 
                      //flagΪż����ʾ���Ը�������
                      //flagΪ������ʾ��Ҹ�������

int board[23][24] = { 0 };      //0��ʾû������״̬
							   //1��ʾ��������ҵ�����
							   //2��ʾ�����е��Ե�����

int judge();    //�ж���Ӯ


void initGame()    //��ʼ����Ϸ
{
	//��ͼ����
	initgraph(670, 650);      //ͼ�δ��ڴ�СΪ600x500
	//��ͼ
	loadimage(NULL, "chess.jpg");
	//BGM();
	setlinecolor(BLACK);        //����������Ϊ��ɫ
	//��������
	//����
	for (int i = 25;i <= 525;i += 25)
	{
		line(i + 25, 75, i + 25, 575);
		line(50, i + 50, 550, i + 50);
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
	settextstyle(18, 0, "����");                 //�����ұ����ֵĴ�С����ʽ
	outtextxy(565, 150, "���1:����");            //�������ұߴ�ӡ��������ִ����ɫ
	fillroundrect(560, 240, 660, 280, 10, 10);   //��Բ�Ǿ���
	outtextxy(565, 250, "���2:����");            //�������ұߴ�ӡ�������ִ����ɫ

	settextstyle(35, 0, "����");                 //��ӡ�������ұ�VS����ַ����Ĵ�С����ʽ
	settextcolor(RED);                          //��ӡ�������ұ�VSΪ��ɫ
	outtextxy(590, 192, "VS");                   //��ӡ��VS����ַ���


	//�����̶��ϴ�ӡ������
	settextstyle(27, 0, "����");               //�����̶��ϵ����ֵĴ�С����ʽ
	settextcolor(BLACK);                       //�����̶��ϵ����ֵ���ɫΪ��ɫ
	setfillcolor(GREEN);
	outtextxy(25, 10, "���1������");
	outtextxy(40, 40, "������");
	fillrectangle(125, 40, 175, 70);          //���ľ��ο�
	outtextxy(143, 42, '0' + 0);              //��ʼ�����1����Ϊ0                                 
	outtextxy(490, 10, "���2������");        //���ַ���0��+����ת��Ϊ�����ַ��������������������������仯������
	outtextxy(505, 40, "������");
	fillrectangle(590, 40, 645, 70);          //���ľ��ο�
	outtextxy(608, 42, '0' + 0);              //��ʼ�����2����Ϊ0

	//�����̶��ϴ�ӡʤ��״��
	outtextxy(260, 10, "���1:");
	outtextxy(335, 10, " ���2");
	//�����ַ�ֻ�����10�����ַ���������Ҫ�������²���
	//����������1ʤ��������10��Ĵ���
	if (count11 < 10)
	{
		outtextxy(290, 40, '0' + count11);    //��ӡ�����1��ʤ����
	}
	if (count11 >= 10)
	{
		outtextxy(280, 40, '0' + count11 / 10);    //��ӡ�����1��ʤ������ʮλ��
		outtextxy(295, 40, '0' + count11 % 10);    //��ӡ�����1��ʤ�����ĸ�λ��
	}
	//�������2ʤ��������10��Ĵ���
	if (count22 < 10)
	{
		outtextxy(330, 40, ":");
		outtextxy(370, 40, '0' + count22);    //��ӡ�����2��ʤ����
	}
	if (count22 >= 10)
	{
		outtextxy(330, 40, ":");
		outtextxy(366, 40, '0' + count22 / 10);    //��ӡ�����2��ʤ������ʮλ��
		outtextxy(380, 40, '0' + count22 % 10);    //��ӡ�����2��ʤ�����ĸ�λ��
	}

	//���̵ײ������֣���ʾ��ҿ��Խ��еĲ���
	setfillcolor(YELLOW);              //���ο�������ɫ
	settextstyle(23, 0, NULL);           //���ο������ֵĴ�С����ʽ
	fillrectangle(35, 600, 140, 630);    //���ļ������ο�
	fillrectangle(535, 600, 640, 630);
	fillrectangle(260, 600, 415, 630);
	outtextxy(40, 605, "���¿�ʼ");      //���ο��ڵ�����
	outtextxy(540, 605, "�˳���Ϸ");
	outtextxy(265, 605, "�˳�˫�˶�ս");

	//�������½ǵ����֣���ʾ��˭����
	//�����Ƚ��д�ӡ��Ϊ�˺���ֱ���ñ���ɫ���Ǽ��ɣ�ֱ�ӷ�����������������˸
	setfillcolor(WHITE);                 //��ӡ��˭���ӵľ��ο�������ɫΪ��ɫ
	fillrectangle(570, 350, 620, 530);   //���ľ��ο�
	settextstyle(30, 0, NULL);           //��ӡ�ĸ�˭�������ֵĴ�С����ʽ
	outtextxy(580, 360, "��");
	outtextxy(580, 400, "��");
	outtextxy(580, 440, "��");
	outtextxy(580, 480, "��");
}

//����
void playChess()
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
				if (abs(m.x - i * 25) < 12 && abs(m.y - j * 25) < 12)  //����ֵ
				{
					a = i;
					b = j;
				}
			}
		}
		
		//����������
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			setbkcolor(WHITE);     //��ӡ��������ľ��ο�������ɫΪ��ɫ

			//����Ϊ����������֪����ʱ��˭������
			if (flag % 2 == 0)    //���flagΪż����˵���ð���������
			{
				clearrectangle(570, 350, 620, 530);
				outtextxy(580, 360, "��");
				outtextxy(580, 400, "��");
				outtextxy(580, 440, "��");
				outtextxy(580, 480, "��");
				
			}
			else                  //���flagΪ������˵���ú���������
			{
				clearrectangle(570, 350, 620, 530);
				outtextxy(580, 360, "��");
				outtextxy(580, 400, "��");
				outtextxy(580, 440, "��");
				outtextxy(580, 480, "��");
			}
			//�ж�����Ƿ���Ҫ�������¿�ʼ���˳�AI��ս���˳���Ϸ����
			if (m.x > 35 && m.x < 140 && m.y>600 && m.y < 630)        //�������¿�ʼAI��ս�ľ��η�Χ
			{
				//���forѭ��������Ϊ���ܹ���ȫ�ֱ�������������Ϊ0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board[i][j] = 0;
					}
				}
				step11 = 0, step22 = 0;    //֮ǰ��¼�Ĳ���������ֵΪ0
				player();                 //�ٴν���˫�˶�ս
			}
			if (m.x > 535 && m.x < 640 && m.y>600 && m.y < 630)    //�����˳���Ϸ�ľ��ο�Χ
			{
				exit(0);  //�˳���Ϸ
			}
			if (m.x > 260 && m.x < 415 && m.y>600 && m.y < 630)    //�����˳�AI��ս�ľ��ο�Χ
			{
				//���forѭ��������Ϊ���ܹ���ȫ�ֱ�������������Ϊ0
				for (int i = 2;i < 23;i++)
				{
					for (int j = 3;j < 24;j++)
					{
						board[i][j] = 0;
					}
				}
				step11 = 0, step22 = 0;         //֮ǰ��¼�Ĳ���������ֵΪ0
				count11 = 0, count22 = 0;        //֮ǰ��¼��ʤ��״��ȫ������ֵΪ0
				break;                          //�˳����ѭ����Ϊ�˽������˫�˶�ս�����½���main()����
			}
			//�ص�
			if (board[a][b] != 0)
			{
				MessageBox(NULL, "�����Ѿ��������ˣ�������ѡ��", "��ʾ", MB_OK);
				continue;   //�˳�ѭ�����½���
			}
			if (flag % 2 == 0)      //ż���������1����
			{
				setfillcolor(BLACK);
				solidcircle(a * 25, b * 25, 10);
				board[a][b] = 1;

				//��ӡ���1����
				step11++;                           //���1������һ
				setbkcolor(GREEN);                    //������ɫΪ��ɫ
				clearrectangle(125, 40, 175, 70);     //�������ɫ����֮ǰ�Ĳ���
				//�����ַ����ֻ����10���ڵ��ַ������Գ���10��Ҫ�������²���
				if (step11 < 10)
				{
					outtextxy(143, 42, '0' + step11);    //��ӡ�����1�Ĳ���
				}
				if (step11 >= 10)
				{
					outtextxy(136, 42, '0' + step11 / 10);    //��ӡ�����1�Ĳ�����ʮλ��
					outtextxy(150, 42, '0' + step11 % 10);    //��ӡ�����1�Ĳ����ĸ�λ��
				}
			}
			else       //�����������2����
			{
				setfillcolor(WHITE);
				solidcircle(a * 25, b * 25, 10);
				board[a][b] = 2;

				//��ӡ���2����
				step22++;                           //���2������һ
				setbkcolor(GREEN);                   //������ɫΪ��ɫ
				clearrectangle(590, 40, 645, 70);    //�������ɫ����֮ǰ�Ĳ���
				//�����ַ����ֻ����10���ڵ��ַ������Գ���10��Ҫ�������²���
				if (step22 < 10)
				{
					outtextxy(608, 42, '0' + step22);         //��ӡ�����2�Ĳ���
				}
				if (step22 >= 10)
				{
					outtextxy(601, 42, '0' + step22 / 10);    //��ӡ�����2�Ĳ�����ʮλ��
					outtextxy(615, 42, '0' + step22 % 10);    //��ӡ�����2�Ĳ����ĸ�λ��

				}
			}
			flag++;
		}
		if (judge())
		{
			if (flag % 2 == 0)
			{
				count22++;                 //���2Ӯ�ˣ�������ʤ�����ı�����һ
				k = load_count();           //�Ѵ�������������ļ��д򿪣���ֵ����k
				save_count(k);             //������һ�ε������������save_count������AI.dat�ļ���
				save_record(flag);        //����һ��˫�˶�ս��ս�������ļ�AI.txt��

				//�ж�����Ƿ���Ҫ����˫�˶�ս
				int isok = MessageBox(NULL, "���2ʤ�����Ƿ���Ҫ����˫�˶�ս", "��Ϸ����", MB_OKCANCEL);
				if (isok == IDOK)
				{
					//���forѭ��������Ϊ���ܹ���ȫ�ֱ�������������Ϊ0
					for (int i = 2;i < 23;i++)
					{
						for (int j = 3;j < 24;j++)
						{
							board[i][j] = 0;
						}
					}
					step11 = 0, step22 = 0;         //֮ǰ��¼�Ĳ���������ֵΪ0
					player();                 //�ٴν���˫�˶�ս
				}
				else if (isok == IDCANCEL)
				{
					exit(0);     //�˳���Ϸ
				}
			}
			else
			{
				count11++;               //���1Ӯ�ˣ�������ʤ�����ı�����һ
				k = load_count();           //�Ѵ�������������ļ��д򿪣���ֵ����k
				save_count(k);             //������һ�ε������������save_count������AI.dat�ļ���
				save_record(flag);        //����һ��˫�˶�ս��ս�������ļ�AI.txt��

				//�ж�����Ƿ���Ҫ����˫�˶�ս
				int isok1 = MessageBox(NULL, "���1ʤ�����Ƿ���Ҫ����˫�˶�ս", "��Ϸ����", MB_OKCANCEL);
				if (isok1 == IDOK)
				{
					//���forѭ��������Ϊ���ܹ���ȫ�ֱ�������������Ϊ0
					for (int i = 2;i < 23;i++)
					{
						for (int j = 3;j < 24;j++)
						{
							board[i][j] = 0;
						}
					}
					step11 = 0, step22 = 0;        //֮ǰ��¼�Ĳ���������ֵΪ0
					player();                 //�ٴν���˫�˶�ս
				}
				else if (isok1 == IDCANCEL)
				{
					exit(0);    //�˳���Ϸ
				}
			}
		}
	}
}

//�ж���Ϸ��Ӯ
int judge()
{
	int i, j;
	//�����ж��Ƿ��Ѿ���������
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 24;j++)
		{
			if (board[i][j] == board[i + 1][j] && board[i + 1][j] == board[i + 2][j] && board[i + 2][j] == board[i + 3][j] && board[i + 3][j] == board[i + 4][j] && board[i][j] != 0)
				return 1;
		}
	}
	//�����ж��Ƿ��Ѿ���������
	for (i = 2;i < 23;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board[i][j] == board[i][j + 1] && board[i][j + 1] == board[i][j + 2] && board[i][j + 2] == board[i][j + 3] && board[i][j + 3] == board[i][j + 4] && board[i][j] != 0)
				return 1;
		}
	}
	//��б�ж��Ƿ��Ѿ���������
	for (i = 2;i < 19;i++)
	{
		for (j = 3;j < 20;j++)
		{
			if (board[i][j] == board[i + 1][j + 1] && board[i + 1][j + 1] == board[i + 2][j + 2] && board[i + 2][j + 2] == board[i + 3][j + 3] && board[i + 3][j + 3] == board[i + 4][j + 4] && board[i][j] != 0)
				return 1;
		}
	}
	//��б�ж��Ƿ��Ѿ���������
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
	initGame();    //�������̳�ʼ��
	while (1)
	{
		playChess();   //������ʽ����
		break;
	}
	
	return 0;
}