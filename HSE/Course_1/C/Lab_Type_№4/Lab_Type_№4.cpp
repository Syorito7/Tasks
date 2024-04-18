
#include <stdio.h>
#include <stdlib.h>

void create_arr(int* arr, int size);// заполнение массива (указатель на 1-ый элемент массива, размер массива)
void print_arr(int* arr, int size);// вывод массива (указатель на 1-ый элемент массива, размер массива)
int search_max_arr(int* arr, int size, int y);// возвращает индекс на 1-ый максимальный элемент в массиве (указатель на 1-ый элемент массива, размер массива)
double sum_max_1st_span_last_div_2_arr(int* arr, int size, int ind_max); // возвращает сумму от 1-ого максимального до последнего чётного элемента ((указатель на 1-ый элемент массива, размер массива, индекс макс. эл)

//sizeof - функция, которая возвращает число выделенных байт на массив, поэтому делю на 4, так как 1 эмемент весит 4 байта

int main()
{
    int mass[10];// выделяется память на целочисленный массив с размером "10"
    create_arr(mass, sizeof(mass) / 4); // заполнение массива
    print_arr(mass, sizeof(mass) / 4); // вывод всех элементов массива
    int d = 0;
    printf("Enter y=");
    scanf_s("%d", &d);
    printf("mass(max)=%d\n", mass[search_max_arr(mass, sizeof(mass) / 4,d)]); // вывод максимального элемента массива
    printf("sum=%lf", sum_max_1st_span_last_div_2_arr(mass, sizeof(mass) / 4, search_max_arr(mass, sizeof(mass) / 4,d))); // вывод суммы
}

void create_arr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("Enter mass[%d]=", i);
        scanf_s("%d", &arr[i]);
    }
}

void print_arr(int* arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("mass[%d]=%d\n", i, arr[i]);
    }
}

int search_max_arr(int* arr, int size, int y)
{
    int tmp_max = arr[0], ind = 0;
    for (int i = 1; i < size; i++)
    {
        if ((abs(tmp_max) < abs(arr[i]))&&(y>=arr[i]))
        {
            tmp_max = arr[i];
            ind = i;
        }
    }
    return ind;
}

double sum_max_1st_span_last_div_2_arr(int* arr, int size, int ind_max)
{
    int ind_2 = 0, k = 0;
    double sum = 0;
    for (int i = size - 1; i >= 0; i--)
    {
        if (arr[i] % 2 == 0)
        {
            ind_2 = i;
            break;
        }
    }
    if ((abs(ind_2 - ind_max) == 1)||(ind_2==ind_max))
    {
        return 0;
    }
    if (ind_2 > ind_max)
    {
        for (int i = ind_max + 1; i < ind_2; i++)
        {
            sum += arr[i];
            k++;
        }
    }
    else
    {
        for (int i = ind_2 + 1; i < ind_max; i++)
        {
            sum += arr[i];
        }
    }
    if (k==0)
    {
        return 0;
    }
    return sum / k;
}

/* написать программу, которые принимает отдельные слова. Разделительные знаки - \n. Если слова совпадают полностью, то вывести все уникальные слова по одному разу. При этом выделение памяти под каждое слово должно происходить динамически. ПО окончанию ввода - */