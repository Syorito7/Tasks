#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Football_league.h"


Club database[100];
int index_club = 0;

// --------- ������� ��������, �������� � ������ ����� ----

int delete_data(); // ������� ������
void move_database_to_file();//������� ������ �� ������� � ����
void print_data(int index); // ����� ��������� �����
int print_all_data(); // ����� ���� ������

// ---------- ������ ���������� �� ���� -------------------

int search_data();// ����� �� ���� ����
void search_name_trainer(); // ����� �� ����� �������
void search_beetween_goals_on_of(); // ����� �� ������� �����
void search_score(); // ����� �� �����
void search_name_city(); // ����� �� �������� ������
void search_name_club(); // ����� �� �������� �����



// ----------- ������� ���������� ���� --------------------

void add_name_trainer(); // �������� ��� �������
void add_name_Club();  // �������� �������� �����
void add_name_city(); // �������� �������� ������
int add_data(); // �������� ������



// ----------- ������� ��� ������������ ���� --------------

int rename_data();
void rename_name_trainer(int* index); // ������������� �������
void rename_beetween_goals_on_of(int* index); // �������� ������� �����
void rename_score(int* index); // �������� ���-�� �����
void rename_city(int* index); // ������������� �����
void rename_club(int* index); // ������������� ����



// ----------- ������� ���������� -------------------------

int sort_data(); // ���������� �� ������ ����. ������� ������������ ������ �������� � �������� ������� !!!


int main()
{
	while (1)
	{
		printf("List commands : \n1 - Adding information\n2 - Deleting information\n3 - Element search\n");
		printf("4 - Editing element\n5 - Sorting\n6 - Print all database\n7 - Console cleaning\n0 - Exit\n");
		int command;
		scanf_s("%d", &command);
		switch (command)
		{
		case 1:
			add_data();
			// ���������� ������ � ���� - �������!
			break;
		case 2:
			delete_data();
			// �������� �������� ������ �� ���� - �������!
			break;
		case 3:
			search_data();
			// ����� ������� �� ��������� ������������ (������) ���� - �������!
			break;
		case 4:
			rename_data();
			// �������������� �������� ������ � ���� (����� ����) - �������!
			break;
		case 5:
			sort_data();
			// ���������� ������ � ���� �� ��������� ������������� (������) ���� - ������� !
			break;
		case 6:
			print_all_data();
			// ����� �� ����� ����������� ���� � ��������� ����
			break;
		case 0:
			// �����
			exit(1);
			break;
		case 7:
			system("cls"); // ������� ����
			break;
		default:
			printf("This command isn't working\n");
			break;
		}
	}
}

int search_data()
{
	if (index_club == 0)
	{
		printf("No data!\n");
		return 1;
	}
	printf("Select point\n");
	int choice = 0;
	while (1)
	{
		printf("1 - name_club\n2 - name_city\n3 - score\n4 - beetween_goals_on_of\n5 - name_trainer\nYour choice : ");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			// ����� ����� - C������!
			search_name_club();
			return 0;
		case 2:
			search_name_city();
			// ����� ������ - �������!
			return 0;
		case 3:
			search_score();
			// ����� �� ����� - �������!
			return 0;
		case 4:
			search_beetween_goals_on_of();
			// ����� �� �������� ������� ����� - �������!
			return 0;
		case 5:
			search_name_trainer();
			// ����� �� ����� ������� - �������!
			return 0;
		default:
			printf("This command doesn't exist\n");
			break;
		}
	}
}

void search_name_trainer()
{
	char* tmp_name_trainer = (char*)malloc(sizeof(char) * 256);
	char tmp_char;
	int int_switch = 0, tr = 0, tmp_index = 0;
	printf("Name trainer : ");
	scanf_s("%c", &tmp_char);
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp_char);
		if (tmp_char == '\n')
		{
			tmp_index = i;
			tmp_char = 0;
			tmp_name_trainer[i] = tmp_char;
			break;
		}
		tmp_name_trainer[i] = tmp_char;
	}
	for (int i = 0; i < index_club; i++)
	{
		tr = 0;
		for (int l = 0; l <= tmp_index; l++)
		{
			if (database[i].name_trainer[l] != tmp_name_trainer[l])
			{
				tr = 1;
				break;
			}
		}
		if (tr == 0)
		{
			int_switch = 1;
			print_data(i);
		}
	}
	free(tmp_name_trainer);
	if (int_switch == 1) printf("Successfully found!\n");
	else printf("There is no such data\n");
}

void search_beetween_goals_on_of()
{
	printf("beetween goals on of : ");
	int tmp_goals, int_switch = 0;
	scanf_s("%d", &tmp_goals);
	for (int i = 0; i < index_club; i++)
	{
		if (database[i].beetween_goals_on_of == tmp_goals)
		{
			int_switch = 1;
			print_data(i);
		}
	}
	if (int_switch == 1) printf("Successfully found!\n");
	else printf("There is no such data\n");
}

void search_score()
{
	printf("Score : ");
	int tmp_score, int_switch = 0;
	scanf_s("%d", &tmp_score);
	for (int i = 0; i < index_club; i++)
	{
		if (database[i].score == tmp_score)
		{
			int_switch = 1;
			print_data(i);
		}
	}
	if (int_switch == 1) printf("Successfully found!\n");
	else printf("There is no such data\n");
}

void search_name_city()
{
	char* tmp_name_city = (char*)malloc(sizeof(char) * 256);
	char tmp_char;
	int tmp_index, int_switch = 0;
	printf("Name city : ");
	scanf_s("%c", &tmp_char);
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp_char);
		if (tmp_char == '\n')
		{
			tmp_index = i;
			tmp_char = 0;
			tmp_name_city[i] = tmp_char;
			break;
		}
		tmp_name_city[i] = tmp_char;
	}
	int tr = 0;
	for (int i = 0; i < index_club; i++)
	{
		tr = 0;
		for (int l = 0; l <= tmp_index; l++)
		{
			if (database[i].name_city[l] != tmp_name_city[l])
			{
				tr = 1;
				break;
			}
		}
		if (tr == 0)
		{
			int_switch = 1;
			print_data(i);
		}
	}
	free(tmp_name_city);
	if (int_switch == 1) printf("Successfully found!\n");
	else printf("There is no such data\n");
}

void search_name_club()
{
	char* tmp_name_club = (char*)malloc(sizeof(char) * 256);
	char tmp_char;
	int tmp_index, int_switch = 0;
	printf("Name club : ");
	scanf_s("%c", &tmp_char);
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp_char);
		if (tmp_char == '\n')
		{
			tmp_index = i;
			tmp_char = 0;
			tmp_name_club[i] = tmp_char;
			break;
		}
		tmp_name_club[i] = tmp_char;
	}
	int tr = 0; // ���� �� ����� ������
	for (int i = 0; i < index_club; i++)
	{
		tr = 0;
		for (int l = 0; l <= tmp_index; l++)
		{
			if (database[i].name_club[l] != tmp_name_club[l])
			{
				//printf("%c", database[i].name_club[l]);
				tr = 1; // ���� �� ��������
				break;
			}
		}
		if (tr == 0)
		{
			int_switch = 1;
			// ����� ���������� ������
			print_data(i);
		}
	}
	free(tmp_name_club);
	if (int_switch == 1) printf("Successfully found!\n");
	else printf("There is no such data\n");
}


void print_data(int index)
{
	printf("name Club : ");
	for (int j = 0; j < 256; j++)
	{
		if (database[index].name_club[j] == 0) break;
		printf("%c", database[index].name_club[j]);
	}
	printf("\nname city : ");
	for (int j = 0; j < 256; j++)
	{
		if (database[index].name_city[j] == 0) break;
		printf("%c", database[index].name_city[j]);
	}
	printf("\nscore : %d", database[index].score);
	printf("\nbeetween goals on of : %d", database[index].beetween_goals_on_of);
	printf("\nname traner : ");
	for (int j = 0; j < 256; j++)
	{
		if (database[index].name_trainer[j] == 0) break;
		printf("%c", database[index].name_trainer[j]);
	}
	printf("\n");
}


int delete_data()
{
	if (index_club == 0)
	{
		printf("No data\n");
		return 2;
	}
	int index_deleted_data;
	printf("Enter number data :");
	scanf_s("%d", &index_deleted_data);
	if (index_deleted_data >= index_club)
	{
		printf("This data isn't in base\n");
		return 1;
	}
	for (int i = index_deleted_data; i < index_club - 1; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			*(database[i].name_club + j) = *(database[i + 1].name_club + j);
		}
		for (int j = 0; j < 256; j++)
		{
			*(database[i].name_city + j) = *(database[i + 1].name_city + j);
		}
		database[i].score = database[i + 1].score;
		database[i].beetween_goals_on_of = database[i + 1].beetween_goals_on_of;
		for (int j = 0; j < 256; j++)
		{
			*(database[i].name_trainer + j) = *(database[i + 1].name_trainer + j);
		}
	}
	index_club--;
	printf("Database changed\n");
	move_database_to_file();
}

void add_name_trainer()
{
	char tmp;
	char* tmp_name_trainer = (char*)malloc(sizeof(char) * 256);
	scanf_s("%c", &tmp);
	int end = 0;
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp);
		if (tmp == '\n')
		{
			tmp = 0;
			tmp_name_trainer[i] = tmp;
			break;
		}
		tmp_name_trainer[i] = tmp;
		end++;
	}
	for (int i = 0; i <= end; i++)
	{
		*(database[index_club].name_trainer + i) = tmp_name_trainer[i];
	}
	free(tmp_name_trainer);
}

void add_name_Club()
{
	char tmp;
	char* tmp_name_Cl = (char*)malloc(sizeof(char) * 256);
	scanf_s("%c", &tmp);
	int end = 0;
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp);
		if (tmp == '\n')
		{
			tmp = 0;
			tmp_name_Cl[i] = tmp;
			break;
		}
		tmp_name_Cl[i] = tmp;
		end++;
	}
	for (int i = 0; i <= end; i++)
	{
		*(database[index_club].name_club + i) = tmp_name_Cl[i];
	}
	free(tmp_name_Cl);
}

void add_name_city()
{
	char tmp;
	char* tmp_name_city = (char*)malloc(sizeof(char) * 256);
	int end = 0;
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp);
		if (tmp == '\n')
		{
			tmp = 0;
			tmp_name_city[i] = tmp;
			break;
		}
		tmp_name_city[i] = tmp;
		end++;
	}
	for (int i = 0; i <= end; i++)
	{
		*(database[index_club].name_city + i) = tmp_name_city[i];
	}
	free(tmp_name_city);
}

int add_data()
{
	if (index_club == 100)
	{
		printf("User didn't can to create or to add new club, Because there is no memory access\n");
		return 1;
	}
	printf("Fill in the information\n");
	printf("Name Club : ");
	add_name_Club();
	//puts(database[index_club].name_club);
	printf("Name city : ");
	add_name_city();
	printf("Score : ");
	scanf_s("%d", &database[index_club].score);
	printf("Beetween_goals_on_of : ");
	scanf_s("%d", &database[index_club].beetween_goals_on_of);
	database[index_club].score = abs(database[index_club].score);
	database[index_club].beetween_goals_on_of = abs(database[index_club].beetween_goals_on_of);
	printf("Coach's name : ");
	add_name_trainer();
	index_club++;
	printf("Data saved!\n");
	move_database_to_file();
}

void rename_club(int* index)
{
	printf("Name club : ");
	char* tmp_name_Cl = (char*)malloc(sizeof(char) * 256);
	char tmp;
	scanf_s("%c", &tmp);
	int end = 0;
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp);
		if (tmp == '\n')
		{
			tmp = 0;
			tmp_name_Cl[i] = tmp;
			break;
		}
		tmp_name_Cl[i] = tmp;
		end++;
	}
	for (int i = 0; i <= end; i++)
	{
		*(database[*index].name_club + i) = tmp_name_Cl[i];
	}
	free(tmp_name_Cl);
	printf("Change completed!\n");
	move_database_to_file();
}

void rename_city(int* index)
{
	printf("Name city : ");
	char* tmp_name_city = (char*)malloc(sizeof(char) * 256);
	char tmp;
	scanf_s("%c", &tmp);
	int end = 0;
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp);
		if (tmp == '\n')
		{
			tmp = 0;
			tmp_name_city[i] = tmp;
			break;
		}
		tmp_name_city[i] = tmp;
		end++;
	}
	for (int i = 0; i <= end; i++)
	{
		*(database[*index].name_city + i) = tmp_name_city[i];
	}
	free(tmp_name_city);
	printf("Change completed!\n");
	move_database_to_file();
}

void rename_score(int* index)
{
	printf("Score : ");
	int tmp_score = 0;
	scanf_s("%d", &tmp_score);
	database[*index].score = abs(tmp_score);
	printf("Change completed!\n");
	move_database_to_file();
}

void move_database_to_file()
{
	FILE* f = fopen("f.bin", "wb");
	for (int i = 0; i < index_club; i++) // ������� ������ �� ������� � ����
	{
		fwrite(database[i].name_club, sizeof(char) * 256, 1, f);
		fwrite(database[i].name_city, sizeof(char) * 256, 1, f);
		fwrite(&database[i].score, sizeof(int), 1, f);
		fwrite(&database[i].beetween_goals_on_of, sizeof(int), 1, f);
		fwrite(&database[i].name_trainer, sizeof(char) * 256, 1, f);
	}
	fclose(f);
}

void rename_beetween_goals_on_of(int* index)
{
	printf("beetween goals on of : ");
	int tmp_goals = 0;
	scanf_s("%d", &tmp_goals);
	database[*index].beetween_goals_on_of = abs(tmp_goals);
	printf("Change completed!\n");
	move_database_to_file();
}

void rename_name_trainer(int* index)
{
	printf("Name trainer : ");
	char* tmp_name_trainer = (char*)malloc(sizeof(char) * 256);
	char tmp;
	scanf_s("%c", &tmp);
	int end = 0;
	for (int i = 0; i < 256; i++)
	{
		scanf_s("%c", &tmp);
		if (tmp == '\n')
		{
			tmp = 0;
			tmp_name_trainer[i] = tmp;
			break;
		}
		tmp_name_trainer[i] = tmp;
		end++;
	}
	for (int i = 0; i <= end; i++)
	{
		*(database[*index].name_trainer + i) = tmp_name_trainer[i];
	}
	free(tmp_name_trainer);
	printf("Change completed!\n");
	move_database_to_file();
}
int rename_data()
{
	if (index_club == 0)
	{
		printf("No data!\n");
		return 2;
	}
	printf("Enter the number data : ");
	int index_data;
	scanf_s("%d", &index_data);
	if (index_data >= index_club)
	{
		printf("This data doesn't in database\n");
		return 1;
	}
	int choice;
	while (1)
	{
		printf("1 - name_club\n2 - name_city\n3 - score\n4 - beetween_goals_on_of\n5 - name_trainer\nYour choice : ");
		scanf_s("%d", &choice);
		switch (choice)
		{
		case 1:
			rename_club(&index_data);
			// �������� ���� - ������� !
			return 0;
		case 2:
			rename_city(&index_data);
			// �������� ����� - ������� !
			return 0;
		case 3:
			rename_score(&index_data);
			// �������� ���-�� ����� - ������� !
			return 0;
		case 4:
			rename_beetween_goals_on_of(&index_data);
			// �������� ������� ������� ����� 
			return 0;
		case 5:
			rename_name_trainer(&index_data);
			// �������� ��� ������� - ������� !
			return 0;
		default:
			printf("This command doesn't exist\n");
			break;
		}
	}
}

int sort_data()
{
	if (index_club == 0)
	{
		printf("No data!\n");
		return 2;
	}
	printf("Select the field you want to sort by : \n");
	int choice = 0;
	printf("1 - Sort by clubs\n2 - Sort by city\n3 - Sort by score\n4 - Sort by goals\n5 - Sort by name trainer\n");
	printf("Your choice : ");
	scanf_s("%d", &choice);
	if ((choice > 5) || (choice < 1))
	{
		printf("This command isn't working\n");
		return 1;
	}
	Club* tmp = (Club*)malloc(sizeof(Club));
	for (int L = 0; L < index_club - 1; L++)
	{
		for (int i = 0; i < index_club - 1; i++)
		{
			if ((((database[i].score > database[i + 1].score) && (choice == 3)) || ((database[i].beetween_goals_on_of > database[i + 1].beetween_goals_on_of) && (choice == 4)) || ((strcmp(database[i].name_club, database[i + 1].name_club) > 0) && (choice == 1))) || ((strcmp(database[i].name_city, database[i + 1].name_city) > 0) && (choice == 2)) || ((strcmp(database[i].name_trainer, database[i + 1].name_trainer) > 0) && (choice == 5)))
			{
				// ������� ������ � ����� �� ��������� ����
				for (int j = 0; j < 256; j++)
				{
					tmp[0].name_club[j] = database[i].name_club[j];
					if (database[i].name_club[j] == 0) break;
				}
				for (int j = 0; j < 256; j++)
				{
					tmp[0].name_city[j] = database[i].name_city[j];
					if (database[i].name_city[j] == 0) break;
				}
				tmp[0].score = database[i].score;
				tmp[0].beetween_goals_on_of = database[i].beetween_goals_on_of;
				for (int j = 0; j < 256; j++)
				{
					tmp[0].name_trainer[j] = database[i].name_trainer[j];
					if (database[i].name_trainer[j] == 0) break;
				}
				// ������� ������ i+1 �����
				for (int j = 0; j < 256; j++)
				{
					database[i].name_club[j] = database[i + 1].name_club[j];
					if (database[i].name_club[j] == 0) break;
				}
				for (int j = 0; j < 256; j++)
				{
					database[i].name_city[j] = database[i + 1].name_city[j];
					if (database[i].name_city[j] == 0) break;
				}
				database[i].score = database[i + 1].score;
				database[i].beetween_goals_on_of = database[i + 1].beetween_goals_on_of;
				for (int j = 0; j < 256; j++)
				{
					database[i].name_trainer[j] = database[i + 1].name_trainer[j];
					if (database[i].name_trainer[j] == 0) break;
				}
				// ������� ������ �� tmp � ����
				for (int j = 0; j < 256; j++)
				{
					database[i + 1].name_club[j] = tmp[0].name_club[j];
					if (database[i + 1].name_club[j] == 0) break;
				}
				for (int j = 0; j < 256; j++)
				{
					database[i + 1].name_city[j] = tmp[0].name_city[j];
					if (database[i + 1].name_city[j] == 0) break;
				}
				database[i + 1].score = tmp[0].score;
				database[i + 1].beetween_goals_on_of = tmp[0].beetween_goals_on_of;
				for (int j = 0; j < 256; j++)
				{
					database[i + 1].name_trainer[j] = tmp[0].name_trainer[j];
					if (database[i + 1].name_trainer[j] == 0) break;
				}
			}
		}
	}
	printf("Sort!\n");
	print_all_data();
	free(tmp);
}

int print_all_data()
{
	if (index_club == 0)
	{
		printf("No Data!\n");
		return 1;
	}
	printf("-------------All Data-----------------\n");
	int max_size_name_club = 0, max_size_name_city = 0, max_size_name_trainer = 0;
	for (int i = 0; i < index_club; i++)
	{
		if (max_size_name_club < strlen(database[i].name_club)) max_size_name_club = strlen(database[i].name_club);
		if (max_size_name_city < strlen(database[i].name_city)) max_size_name_city = strlen(database[i].name_city);
		if (max_size_name_trainer < strlen(database[i].name_trainer)) max_size_name_trainer = strlen(database[i].name_trainer);
	}
	printf("N       | ");// �����
	printf("Club");
	for (int i = 0; i < max_size_name_club; i++) printf(" ");
	printf("| ");
	printf("City");
	for (int i = 0; i < max_size_name_city; i++) printf(" ");
	printf("| ");
	printf("Score       | ");
	printf("Beetween_goals_on_of | Trainer");
	for (int i = 0; i < max_size_name_trainer; i++) printf(" ");
	printf("|\n");
	for (int i = 0; i < index_club; i++)
	{
		int k = 0;
		int tmp_value = i + 1;
		while (tmp_value > 0)
		{
			tmp_value /= 10;
			k++;
		}
		printf("%d", i + 1);
		for (int j = 0; j < 8 - k; j++) printf(" ");
		printf("| ");
		for (int j = 0; j < max_size_name_club + 4; j++)
		{
			if (j < strlen(database[i].name_club))
			{
				printf("%c", database[i].name_club[j]);
			}
			else
			{
				printf(" ");
			}
		}
		printf("| ");
		for (int j = 0; j < max_size_name_city + 4; j++)
		{
			if (j < strlen(database[i].name_city))
			{
				printf("%c", database[i].name_city[j]);
			}
			else
			{
				printf(" ");
			}
		}
		printf("| ");
		tmp_value = database[i].score;
		k = 0;
		while (tmp_value > 0)
		{
			tmp_value /= 10;
			k++;
		}
		printf("%d", database[i].score);
		for (int j = 0; j < 12 - k; j++)
		{
			printf(" ");
		}
		printf("| ");
		k = 0;
		tmp_value = database[i].beetween_goals_on_of;
		while (tmp_value > 0)
		{
			tmp_value /= 10;
			k++;
		}
		printf("%d", database[i].beetween_goals_on_of);
		for (int j = 0; j < 20 - k; j++)
		{
			printf(" ");
		}
		printf(" | ");
		for (int j = 0; j < max_size_name_trainer + 7; j++)
		{
			if (j < strlen(database[i].name_trainer))
			{
				printf("%c", database[i].name_trainer[j]);
			}
			else
			{
				printf(" ");
			}
		}
		printf("| ");
		printf("\n");
	}
}
 