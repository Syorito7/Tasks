
#include <stdio.h>

int n = 0, m = 0;
int mass[10][10] = { 0 }; // создание и инициализирование массива = 0

void enter_n_and_m(int &_n, int &_m); // функция на корректный ввод размерности матрицы (n,m∈[2,10])
void create_arr(int arr[10][10], int _n, int _m); // функция на заполнение входных данных матрицы n*m
void printf_arr(int arr[10][10], int _n, int _m); // функция на вывод матрицы n*m
int sum_last_string_no_more_two_1(int arr[10][10], int _n, int _m); // функция, которая возвращает сумму чисел в последней строке, в которой нашлось не более двух 1

int main()
{
    enter_n_and_m(n, m);
    create_arr(mass, n, m);
    printf_arr(mass, n, m);
    printf("sum=%d", sum_last_string_no_more_two_1(mass, n, m));
}
void enter_n_and_m(int &_n, int &_m)
{
    int tmp_n=0, tmp_m = 0;
    while (!(((tmp_n >= 2) && (tmp_n <= 10)) && ((tmp_m >= 2) && (tmp_m <= 10))))
    {
        printf("Enter n=");
        scanf_s("%d", &tmp_n);
        printf("Enter m=");
        scanf_s("%d", &tmp_m);
    }
    _n = tmp_n;
    _m = tmp_m;
}

void create_arr(int arr[10][10], int _n, int _m)
{
    for (int i = 0; i < _n; i++)
    {
        for (int j = 0; j < _m; j++)
        {
            int tmp;
            scanf_s("%d", &tmp);
            arr[i][j] = tmp;
        }
    }
}

void printf_arr(int arr[10][10], int _n, int _m)
{
    for (int i = 0; i < _n; i++)
    {
        for (int j = 0; j < _m; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int sum_last_string_no_more_two_1(int arr[10][10], int _n, int _m)
{
    int count = 0, sum = 0;
    for (int i = _n - 1; i >= 0; i--)
    {
        sum = 0, count = 0;
        for (int j = 0; j < _m; j++)
        {
            sum += arr[i][j];
            if (arr[i][j] == 1)
            {
                count++;
                if (count > 2)
                    break;
            }
        }
        if (count < 3)
        {
            return sum;
        }
  
    }
    return 0;
}