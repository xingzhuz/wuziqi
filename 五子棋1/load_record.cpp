#define _CRT_SECURE_NO_WARNINGS
#include "game.h"



void load_record()
{
	//ͼ�δ��ڴ�С
	initgraph(670, 900);
	loadimage(NULL, "record.jpg");
	//BGM();
	setbkmode(TRANSPARENT);
	setfillcolor(YELLOW);
	fillrectangle(45, 50, 155, 100);
	fillrectangle(535, 50, 645, 100);
	settextstyle(24, 0, "����");
	settextcolor(BLACK);
	outtextxy(55, 60, "���ز˵�");
	outtextxy(542, 60, "�˳���Ϸ");
	

	int m = 1;
	int v = 0;       
	v = load_count();  //��AI.dat�ļ������������洢��V
	int i;
	char buf[200] = { 0 };
	FILE* pt = fopen("AI.txt","r");   //��AI.txt�ļ��������ж��Ĳ���
	if (pt == NULL)
	{
		return;
	}
	//���ļ�
	settextstyle(20,0, "�п�");    //�����ս����������ʽ
	settextcolor(BLACK);            //�����������ɫ
	setbkmode(TRANSPARENT);        //��������屳��Ϊ͸��
	int h = 150;
	for (i = v;i > 0;i--)
	{
		//�����ַ����ֻ����10���ڵ��ַ������Գ���10��Ҫ�������²���
		if (m < 10)
		{
			outtextxy(160, h, '0' + m);        //��0��h���m������ָ��ֵ
		}
		if (m >= 10)
		{
			outtextxy(155, h, '0' + m / 10);     //��0��h���m������ָ��ֵ��ʮλ��
			outtextxy(165, h, '0' + m % 10);     //��0��h���m������ָ��ֵ�ĸ�λ��
		}
		fgets(buf, 200, pt);          //��ȡAI.txt�ļ����е�����
		outtextxy(200, h, buf);      //��100��h�����ȡ��������
		h =h +25;                    //ִ�н����ݽ������еĲ���
		m++;                         //���ǵ�m++���µ����ս��
	}
	
	fclose(pt);            //�ر��ļ�
	pt == NULL;            //���ļ�ָ����Ϊ��
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