#define _CRT_SECURE_NO_WARNINGS
#include "game.h"

int load_count()
{
	int count2 = 0;
	FILE* pm = fopen("AI.dat", "r");     //��AI.dat�ļ��򿪣�����ֻ���Ĳ���
	if (pm == NULL)
	{
		printf("%s\n", strerror(errno));
	}
	//���ļ�
	fread(&count2, 4, 1, pm);      //��ȡAI.dat�ļ�������ݸ���count2
	fclose(pm);                    //�ر��ļ�
	pm = NULL;                     //���ļ�ָ����Ϊ��
	return count2;                //����ȡ����count2���ݷ���
}