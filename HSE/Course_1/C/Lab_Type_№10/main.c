#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_in_file();// функция вставляет в начало файла кол-во удвоенных нечётных чисел
void print_file(); // выводит содержимое файла
void create_file(); // создаёт файл и пользователь записывает данные в него

int main()
{
	create_file();
	insert_in_file();
	print_file();
}

void insert_in_file()
{
	FILE* f = fopen("f.bin", "r+b");
	int count_value = 0, buffer = 0; // счётчик удвоенных нечётных чисел и счётчик кол-во чисел
	do
	{
		fread(&buffer, sizeof(buffer), 1, f);
		if (feof(f)) break;
		if ((buffer % 2 == 0) && (buffer % 4 != 0))
		{
			count_value++;
		}
	} while (!(feof(f)));
	fseek(f, 0, SEEK_SET);//Каретку в начало преносит
	fwrite(&count_value, sizeof(count_value), 1, f);
	printf("Count: %d\n", count_value);
	fclose(f);
}

void print_file()
{
	FILE* f = fopen("f.bin", "rb");
	int buffer = 0;
	printf("File data :\n");
	do
	{
		fread(&buffer, sizeof(buffer), 1, f);
		if (feof(f)) break;
		printf("%d ", buffer);
	} while (!(feof(f)));// проход по всему файлу и вывод на консоль всех элементов
	fclose(f);
}

void create_file()
{
	FILE* f = fopen("f.bin", "wb");
	int buffer = 0;
	printf("Fil in the File\nTo compete the filling - Enter -1:\n");
	fwrite(&buffer, sizeof(buffer), 1, f);
	char tmp[50];
	int k;
	do //заполнение файла
	{
		k = 0;
		gets(tmp);
		if ((tmp[0] == '-') || ((tmp[0] >= '0') && (tmp[0] <= '9')))
		{;
			for (int i = 1; i < strlen(tmp); i++)
			{
				if ((tmp[i] < '0') || (tmp[i] > '9'))
				{
					k = 1;
					break;
				}
			}
		}
		else k = 1;
		if (k == 0)
		{
			buffer=atoi(tmp);
			if (buffer == -1) break;
			fwrite(&buffer, sizeof(buffer), 1, f);
		}
		if (k == 1) printf("Incorrect input\n");
		if (buffer == -1) k = 2;
	} while (k!=2);
	printf("File saved\n");
	fclose(f);
}