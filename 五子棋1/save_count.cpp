#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

int save_count(int j)    //j��������֮ǰ������ܴ���
{
	int count1 = 0;    //��Ϊ�洢��������ı���
	FILE* pn = fopen("AI.dat", "w");    //��AI.dat�ļ�
	if (pn == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	//д�붫�����ļ���
	count1 = j + 1;     //����һ����ͽ��ܴ�����һ
	fwrite(&count1, 4, 1, pn);  //�����ڵ��ܴ���д��AI.dat�ļ���
	                            //���ܴ�����Ϊ���ܸ��õķ���AI.txt���ÿ��ս��
 	fclose(pn);            //�ر�AI.dat�ļ�
	pn = NULL;       //���ļ�ָ����Ϊ��
	return 0;
}