
#include <stdio.h>
#include <cstdlib>

double* create_arr( int _size_arr);
void print_arr(double* arr,  int _size_arr);
int first_negative_arr(double* arr, int _size_arr);

int main()
{
	int size_arr = 0;// кол-во элементов в массиве
	printf("Enter size mass=");
	scanf_s("%d", &size_arr); // ввод в консоль
	//double* arr = (double*)malloc(size_arr*sizeof(double));  // объявление динам. массива с использованием sizeof, чтобы узнать размер double, также malloc для выделение памяти;
	double* arr = NULL;
	arr = create_arr(size_arr);
	if (arr == NULL) // проверка на выделение памяти
	{
		printf("Memory  no allocated\n");
		return 1;
	}
	printf("\n");
	size_arr=first_negative_arr(arr, size_arr);// присвоение size_arr размер модифицированного массива
	print_arr(arr, size_arr);// вывод массива с новым размером
	free(arr); //освобождение памяти
}

double* create_arr(int _size_arr)
{
	double* arr = (double*)malloc(_size_arr * sizeof(double));
	if (arr != NULL)
	{
		for (int i = 0; i < _size_arr; i++)
		{
			double tmp;
			printf("mass[%d]=", i);
			scanf_s("%lf", &tmp);
			arr[i] = tmp;
		}
	}
	return arr;
}

void print_arr(double* arr, int _size_arr)
{
	for (int i = 0; i < _size_arr; i++)
	{
		printf("mass[%d]=", i);
		printf("%lf\n", arr[i]);
	}
}

int first_negative_arr(double* arr, int _size_arr)
{
	int ind_max = 0, max = arr[0]; // индекс максимального элемента и его значение равный по умолчанию нулевому элементу массива
	for (int i = 0; i < _size_arr; i++)
	{
		if (max < arr[i])
		{
			max = arr[i];
			ind_max = i;
		}
	}
	int size = _size_arr;// будет хранить размер обработанного массива
	int count_del = 0; // кол-во элементов, которые надо удалить
	for (int i = 0; i < ind_max; i++)
	{
		if (arr[i] < 0)
		{
			count_del++;
		}
	}
	size -= count_del;
	int now_del = 0; // кол-во элементов, которые уже удалились
	if (count_del != 0) // если нашлись элементы, которые надо удалить
	{
		for (int i = 0; i < _size_arr; i++)
		{
			if (arr[i] < 0)
			{
				for (int j = i; j < _size_arr-1; j++)// сдвиг элементов массива влево
				{
					arr[j] = arr[j + 1];
				}
				now_del++;
				i--;
				if (now_del == count_del) // если кол-во удалённых элементов = эл. сколько нужно удалить, то выходим из цикла
				{
					break;
				}
			}
		}
		for (int i = size; i < _size_arr; i++) // "мусор", который образовался при сдвиге заполняем 0
		{
			arr[i] = 0;
		}
	}
	arr = (double*)realloc(arr, size);
	return size; // возвращение нового размера массива
}

