#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

void file_search(FILE* _f);//проверка на открываемость файла
void file_output(FILE* _f);//вывод содержимого файла
FILE* create_file();// создание и заполнение текстового файла
void insert_into_file(FILE* _f);//создаёт новый файл и копирует в него данные из _f, но '1' заменяет на их кол-во

int main()
{
	printf("Enter the data in the file F. The last char is ~\n");
	FILE* f = create_file();
	insert_into_file(f);
	file_output(f);

}


void file_output(FILE* _f)
{
	printf("Enter the file name :\n");
	char name;
	scanf_s("%c", &name);
	scanf_s("%c", &name);
	if (name == 'f')
	{
		_f = fopen("f.txt", "r");
		file_search(_f);
	}
	else if (name == 'g')
	{
		_f = fopen("g.txt", "r");
		file_search(_f);
	}
	else
	{
		perror("this file does not exist");
	}
	char* tmp_str = malloc(sizeof(char) * 256);
	if (tmp_str != NULL)
	{
		while (fgets(tmp_str, 256, _f))
		{
			printf("%s", tmp_str);
		}
	}
	else
	{
		fclose(_f);
		printf("Memory\n");
		exit(0);
	}
	free(tmp_str);
	fclose(_f);
}

void insert_into_file(FILE* _f)
{
	_f = fopen("f.txt", "r");
	file_search(_f);
	FILE* g = fopen("g.txt", "w");
	int count_1 = 0;
	char number = NULL;
	while (!feof(_f))
	{
		char tmp = fgetc(_f);
		if (tmp != 'я')
		{
			if (tmp == '1')
			{
				count_1++;
			}
			else
			{
				if (count_1 != 0)
				{
					if (count_1 > 99)
					{
						number = (count_1 / 100) + '0';
						fputc(number, g);
						number = ((count_1 / 10) % 10) + '0';
						fputc(number, g);
						number = count_1 % 10 + '0';
						fputc(number, g);
					}
					else if (count_1 > 9)
					{
						number = ((count_1 / 10) % 10) + '0';
						fputc(number, g);
						number = count_1 % 10 + '0';
						fputc(number, g);
					}
					else
					{
						number = count_1 % 10 + '0';
						fputc(number, g);
					}
					fputc(tmp, g);
					count_1 = 0;
				}
				else
				{
					fputc(tmp, g);
				}
			}
		}
		else
		{
			if (count_1 != 0)
			{
				if (count_1 > 99)
				{
					number = (count_1 / 100) + '0';
					fputc(number, g);
					number = ((count_1 / 10) % 10) + '0';
					fputc(number, g);
					number = count_1 % 10 + '0';
					fputc(number, g);
				}
				else if (count_1 > 9)
				{
					number = ((count_1 / 10) % 10) + '0';
					fputc(number, g);
					number = count_1 % 10 + '0';
					fputc(number, g);
				}
				else
				{
					number = count_1 % 10 + '0';
					fputc(number, g);
				}
			}
		}
	}
	fclose(_f);
	fclose(g);
}

FILE* create_file()
{
	FILE* f = fopen("f.txt", "w");
	char tmp = '0';
	while (tmp != NULL)
	{
		scanf_s("%c", &tmp);
		if (tmp == '~')
		{
			tmp = NULL;
		}
		else
		{
			fputc(tmp, f);
		}
	}
	printf("File saved!\n");
	fclose(f);
	return f;
}

void file_search(FILE* _f)
{
	if (_f == NULL)
	{
		perror("");
		exit(0);
	}
}