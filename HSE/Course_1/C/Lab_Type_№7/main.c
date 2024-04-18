#define _CRT_SECURE_NO_WARNINGS // чтобы могли пользоватьс€ строковыми функци€ми (убрать ограничени€)


#include <stdio.h>
#include <string.h> // библиотека, в которой str функции
#include <stdlib.h>

void print_string(char* _str);// функци€, котора€ выводит слова, которые удовлетвор€ют условию задачи
void print_original_str(char* _str);// функци€, котора€ выводит исходную строку 
void scanf_string(char* _str);// функци€, котора€ заполн€ет строку

int main(void) {
    char* s; // объ€вление строки
    s = (void*)malloc(330 * sizeof(char)); // выделение пам€ти
    if (s == NULL)
    {
        printf("Memory is not allocated\n");
        return 1;
    }
    printf("Enter string:\n");
    //scanf_string(s); //считывание слов в строку
    fgets(s, 330, stdin);
    print_string(s); // вывод строки, в которой хран€тс€ слова по условию задачи
    printf("Original string:\n");
    //print_original_str(s); // вывод исходной строки
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
        char str_2[338] = "String:\n"; // строка, в которой будут хранитьс€ все подход€щие слова по условию
        str_1 = strcpy(str_1, _str); // strcpy - копирует строку str в str_1 (включа€ '\0'), возвращает указатель на str_1 (char*)
        int str_in_1_word = 0; // счЄтчик кол-во слов
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
        else if (str_in_1_word == 1) // проверка на слова
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
        else // если 3 и более
        {
            char* word_1, * word_2, * word_3; // объ€вление строк и выделение пам€ти
            word_1 = (void*)malloc(10 * sizeof(char));
            word_2 = (void*)malloc(10 * sizeof(char));
            word_3 = (void*)malloc(10 * sizeof(char));
            if ((word_1 == NULL) || (word_2 == NULL) || (word_3 == NULL))
            {
                printf("Memory is not allocated in function <print_string>\n");
            }
            else
            {
                word_1 = strtok(str_1, " ,."); // выделение слова из строки str_1 по токенам при помощи strtok - типа char* возвращает указатель на первый элемент не вход€щий в список токенов
                word_2 = strtok(NULL, " ,."); // так как выделили первое слово, то второе начинаетс€ с указател€ который запомнил в прошлом вызове (пишем NULL)
                word_3 = strtok(NULL, " ,."); // аналогично берЄм 3-ье слово
                int i = 0; // счЄтчик проходов в цикле
                while (word_3 != NULL)
                {
                    i++;
                    if (i + 1 == str_in_1_word) break; // чтобы не учитывал случай, когда второе слово €вл€етс€ последним в строке.
                    if ((strcmp(word_2, word_1) > 0) && (strcmp(word_3, word_2) > 0)) // strcmp сравнивает строки, возвращает типа int. если перва€ строка больше 2-ой, то >0, обратное - <0. –авны - 0
                    {
                        strcat(str_2, word_2);//вставка в str_2 слово word_2. “ипа char*
                        strcat(str_2, " ");
                    }
                    word_1 = strcpy(word_1, word_2);
                    word_2 = strcpy(word_2, word_3);
                    word_3 = strtok(NULL, " ,.");
                }
                puts(str_2);
                // аналог вывода строки, написанна€ в библиотеке "string.h". “ип int
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
    for (int i = 0; i < strlen(_str); i++) // функци€ strlen возвращает кол-во символв в строке (int).
    {
        printf("%c", _str[i]);
        if (_str[i] == '.') break;
    }
}