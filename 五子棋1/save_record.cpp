#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

void save_record(int a)   //a����ǰ�洫����flag��ֵ
{ 
	FILE* pf;     //�ļ�ָ��
	pf = fopen("AI.txt", "a");   //��AI.txt�ļ�
	if (pf == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	//aΪż������ʾAIӮ��
	if (a % 2 == 0)
	{ 
		fputs("��AI��ս====", pf);
		fputs("AIʤ�������ϧ�ܣ�\n", pf);
	}
	//aΪ��������ʾ���Ӯ��
	else if (a % 2 == 1)
	{
		fputs("��AI��ս====", pf);
		fputs("���ʤ����\n", pf);
	}
	fclose(pf);   //�ر��ļ�
	pf == NULL;   //���ļ�ָ����Ϊ��
}