#pragma once
typedef struct
{
	int weight; // ���
	int height; // ������
	int width; // ������
} Parametrs; // ��������� ������



typedef struct
{
	char name[256]; // �������� ������
	int coin; // ����
	Parametrs property;
} Set;
