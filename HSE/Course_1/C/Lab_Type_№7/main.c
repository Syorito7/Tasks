#define _CRT_SECURE_NO_WARNINGS // ����� ����� ������������ ���������� ��������� (������ �����������)


#include <stdio.h>
#include <string.h> // ����������, � ������� str �������
#include <stdlib.h>

void print_string(char* _str);// �������, ������� ������� �����, ������� ������������� ������� ������
void print_original_str(char* _str);// �������, ������� ������� �������� ������ 
void scanf_string(char* _str);// �������, ������� ��������� ������

int main(void) {
    char* s; // ���������� ������
    s = (void*)malloc(330 * sizeof(char)); // ��������� ������
    if (s == NULL)
    {
        printf("Memory is not allocated\n");
        return 1;
    }
    printf("Enter string:\n");
    //scanf_string(s); //���������� ���� � ������
    fgets(s, 330, stdin);
    print_string(s); // ����� ������, � ������� �������� ����� �� ������� ������
    printf("Original string:\n");
    //print_original_str(s); // ����� �������� ������
    puts(s);
    free(s);
}

void scanf_string(char* _str)
{
    char tmp;
    int i = 0;
    do
    {
        scanf_s("%c", &tmp);
        _str[i] = tmp;
        i++;
    } while ((tmp != '.') || (tmp != '\n'));
}

void print_string(char* _str)
{
    char* str_1;
    str_1 = (void*)malloc(330 * sizeof(char));
    if (str_1 == NULL)
    {
        printf("Memory is not allocated in function <print_string>\n");
    }
    else
    {
        char str_2[338] = "String:\n"; // ������, � ������� ����� ��������� ��� ���������� ����� �� �������
        str_1 = strcpy(str_1, _str); // strcpy - �������� ������ str � str_1 (������� '\0'), ���������� ��������� �� str_1 (char*)
        int str_in_1_word = 0; // ������� ���-�� ����
        for (int i = 1; i < strlen(_str); i++)
        {
            if (((_str[i] == ',') || (_str[i] == ' ') || (_str[i] == '.')) && (_str[i - 1] != ',') && (_str[i - 1] != ' ') && (_str[i - 1] != '.'))
            {
                str_in_1_word++;
            }
            if (_str[i] == '.')
            {
                break;
            }
        }
        if (str_in_1_word == 0)
        {
            printf("The string consists of zero word\n");
        }
        else if (str_in_1_word == 1) // �������� �� �����
        {
            printf("The string consists of one word\n");
        }
        else if (str_in_1_word == 2)
        {
            printf("the string consists of two words\n");
        }
        else if (str_in_1_word > 29)
        {
            printf("More than 30 words\n");
        }
        else // ���� 3 � �����
        {
            char* word_1, * word_2, * word_3; // ���������� ����� � ��������� ������
            word_1 = (void*)malloc(10 * sizeof(char));
            word_2 = (void*)malloc(10 * sizeof(char));
            word_3 = (void*)malloc(10 * sizeof(char));
            if ((word_1 == NULL) || (word_2 == NULL) || (word_3 == NULL))
            {
                printf("Memory is not allocated in function <print_string>\n");
            }
            else
            {
                word_1 = strtok(str_1, " ,."); // ��������� ����� �� ������ str_1 �� ������� ��� ������ strtok - ���� char* ���������� ��������� �� ������ ������� �� �������� � ������ �������
                word_2 = strtok(NULL, " ,."); // ��� ��� �������� ������ �����, �� ������ ���������� � ��������� ������� �������� � ������� ������ (����� NULL)
                word_3 = strtok(NULL, " ,."); // ���������� ���� 3-�� �����
                int i = 0; // ������� �������� � �����
                while (word_3 != NULL)
                {
                    i++;
                    if (i + 1 == str_in_1_word) break; // ����� �� �������� ������, ����� ������ ����� �������� ��������� � ������.
                    if ((strcmp(word_2, word_1) > 0) && (strcmp(word_3, word_2) > 0)) // strcmp ���������� ������, ���������� ���� int. ���� ������ ������ ������ 2-��, �� >0, �������� - <0. ����� - 0
                    {
                        strcat(str_2, word_2);//������� � str_2 ����� word_2. ���� char*
                        strcat(str_2, " ");
                    }
                    word_1 = strcpy(word_1, word_2);
                    word_2 = strcpy(word_2, word_3);
                    word_3 = strtok(NULL, " ,.");
                }
                puts(str_2);
                // ������ ������ ������, ���������� � ���������� "string.h". ��� int
                free(word_1);
                word_2 = NULL;
                free(word_2);
                word_3 = NULL;
                free(word_3);
            }
        }
        str_1 = NULL;
        free(str_1);
    }
}

void print_original_str(char* _str)
{
    for (int i = 0; i < strlen(_str); i++) // ������� strlen ���������� ���-�� ������� � ������ (int).
    {
        printf("%c", _str[i]);
        if (_str[i] == '.') break;
    }
}