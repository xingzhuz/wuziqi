#include "game.h"
//void BGM();
//void BGM()
//{
//	mciSendString("open ./�ǲ��.mp3", 0, 0, 0);
//	mciSendString("play ./�ǲ��.mp3", 0, 0, 0);
//}


void main()
{
	//��ͼ����
	initgraph(500, 749);
	//��ͼ
	loadimage(NULL, "menu.jpg");
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	//���ĸ���ʼ����
	setfillcolor(BROWN);     //Բ�Ǿ��ε������ɫ
	//�ĸ�Բ�Ǿ��ε�λ��
	fillroundrect(170, 310, 320, 360, 10, 10);    
	fillroundrect(170, 380, 320, 430, 10, 10);
	fillroundrect(170, 450, 320, 500, 10, 10);
	fillroundrect(170, 520, 320, 570, 10, 10);
	settextstyle(30, 0, "�п�");         //Բ�Ǿ������������ʽ����С
	//�ĸ�Բ�Ǿ����ڵ���������
	outtextxy(198,321, "AI��ս");        
	outtextxy(185,391, "˫�˶�ս");
	outtextxy(185,461, "�鿴ս��");
	outtextxy(185,531, "�˳���Ϸ");
	//BGM();    //��������

	MOUSEMSG n;
	while (1)
	{
		n = GetMouseMsg();
		//���Ƕ������λ�õ�ȷ����Ȼ����벻ͬ�ĺ�����ʵ�ֲ�ͬ�Ĺ���
		if (n.uMsg == WM_LBUTTONDOWN)
		{   
			if (n.x > 170 && n.x < 320 && n.y>310 && n.y < 360)
			{
				AI();    //����AI��ս
				break;
			}
			else if (n.x > 170 && n.x < 320 && n.y>380 && n.y < 430)
			{
				player();   //����˫�˶�ս
				break;
			}
			else if (n.x > 170 && n.x < 320 && n.y>450 && n.y < 500)
			{
				load_record();  //����鿴ս��
				break;
			}
			else if (n.x > 170 && n.x < 320 && n.y>520 && n.y < 570)
			{
				exit(0);     //�˳���Ϸ
			}
		}
	}
	main();    //�ٴν�����Ϸ������˵�
}
