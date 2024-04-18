#pragma once
typedef struct
{
	int weight; // Вес
	int height; // Высота
	int width; // Ширина
} Parametrs; // параметры товара



typedef struct
{
	char name[256]; // название товара
	int coin; // цена
	Parametrs property;
} Set;
