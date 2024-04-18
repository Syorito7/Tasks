#include <stdio.h>
#include "Setlib.h"
#include <stdlib.h>
#include <string.h>

#define KEY//ключ

int by_default();//заранее заданные данные и нахождение самого лёгкого товара(товаров) среди них
int action();// ввод пользователем информацию о товарах и нахождения самого лёгкого товара(товаров) среди них


int main()
{
#ifdef KEY
	action();
#endif 
	by_default();
}

int action()
{
	Set data[20];// массив товаров
	int count_set;// кол-во товаров
	char tmp_char;
	printf("Enter the number of products : ");
	scanf_s("%d", &count_set);
	if (count_set > 20)
	{
		printf("Max count product=20\n");
		count_set = 20;
	}
	else if (count_set <= 0) return 1;
	printf("Filling layout\n");
	printf("Name : apple\nCost : 10\nWeight : 300 (gram)\nHeight : 250\nWidth : 270\n");
	for (int i = 0; i < count_set; i++)
	{
		printf("Name : ");
		scanf_s("%c", &tmp_char);
		data[i].name[0] = tmp_char;
		for (int j = 1; j < strlen(data[i].name); j++)
		{
			scanf_s("%c", &data[i].name[j]);
			if (data[i].name[j] == '\n') break;
		}
		printf("Coin :");
		scanf_s("%d", &data[i].coin);
		printf("Weith :");
		scanf_s("%d", &data[i].property.weight);
		printf("Height :");
		scanf_s("%d", &data[i].property.height);
		printf("Width :");
		scanf_s("%d", &data[i].property.width);
		printf("%d-st product completed\n", i + 1);
	}
	printf("Enter the maximum price for the product\nMax coin : ");
	int max_coin = 0;
	scanf_s("%d", &max_coin);
	char name_prod[256];
	int min_weigth = -1;
	for (int i = 0; i < count_set; i++)
	{
		if ((min_weigth == -1) && (data[i].coin <= max_coin))
		{
			min_weigth = data[i].property.weight;
		}
		else if ((data[i].coin <= max_coin) && (min_weigth > data[i].property.weight))
		{
			min_weigth = data[i].property.weight;
		}
	}
	if (min_weigth == -1) printf("There is no such product\n");
	else
	{
		for (int i = 0; i < count_set; i++)
		{
			if ((min_weigth == data[i].property.weight)&&(data[i].coin<=max_coin))
			{
				for (int j = 0; j < strlen(data[i].name); j++)
				{
					if (j == 0)
					{
						printf("%c", data[i].name[j]);
					}
					else if ((' ' <= data[i].name[j]) && (data[i].name[j] <= 'z'))
					{
						printf("%c", data[i].name[j]);
					}
					else
					{
						break;
					}
				}
			}
		}
	}
	printf("\nProduct database :\n");// вывод базы товаров
	for (int i = 0; i < count_set; i++)
	{
		for (int j = 0; j < strlen(data[i].name); j++)
		{
			if (j == 0)
			{
				printf("%c", data[i].name[j]);
			}
			else if ((' ' <= data[i].name[j]) && (data[i].name[j] <= 'z'))
			{
				printf("%c", data[i].name[j]);
			}
			else
			{
				break;
			}
		}
		printf("\nCoin :%d", data[i].coin);
		printf("\nWeith :%d", data[i].property.weight);
		printf("\nHeight :%d", data[i].property.height);
		printf("\nWidth :%d", data[i].property.weight);
		printf("\n%d-st product completed\n", i + 1);
	}
	exit(0);
}


int by_default()
{
	Set data[5] = { "Mineral water", 70,1500,400,200, "Apple", 150,1000,30,25,
	"Bread",50,300,10,15,"Marmelads", 120,100,20,10,"Bigmak", 200,100,25,15 };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < strlen(data[i].name); j++)
		{

			if ((' ' <= data[i].name[j]) && (data[i].name[j] <= 'z'))
			{
				printf("%c", data[i].name[j]);
			}
			else
			{
				break;
			}
		}
		printf("\nCoin :%d", data[i].coin);
		printf("\nWeith :%d", data[i].property.weight);
		printf("\nHeight :%d", data[i].property.height);
		printf("\nWidth :%d", data[i].property.weight);
		printf("\n%d-st product completed\n", i + 1);
	}
	printf("Enter the maximum price for the product\nMax coin : ");
	int max_coin = 0;
	scanf_s("%d", &max_coin);
	char name_prod[256];
	int min_weigth = -1;
	for (int i = 0; i < 5; i++)
	{
		if ((min_weigth == -1) && (data[i].coin <= max_coin))
		{
			min_weigth = data[i].property.weight;
		}
		else if ((data[i].coin <= max_coin) && (min_weigth > data[i].property.weight))
		{
			min_weigth = data[i].property.weight;
		}
	}
	if (min_weigth == -1) printf("There is no such product\n");
	else
	{
		for (int i = 0; i < 5; i++)
		{
			if ((min_weigth == data[i].property.weight) && (data[i].coin <= max_coin))
			{
				for (int j = 0; j < strlen(data[i].name); j++)
				{
					if (j == 0)
					{
						printf("%c", data[i].name[j]);
					}
					else if ((' ' <= data[i].name[j]) && (data[i].name[j] <= 'z'))
					{
						printf("%c", data[i].name[j]);
					}
					else
					{
						break;
					}
				}
				printf("\n");
			}
		}
	}
	exit(0);
}