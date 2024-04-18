#include <stdio.h>
#include <stdlib.h>
#include "List.h"

void push(Node* head, int _value, int _degree);
void print_list(Node* head);
int pop(Node** head);
void adding_list(Node* head);

int main()
{

	Node* head = NULL;
	head = (Node*)malloc(sizeof(Node));
	if (head == NULL) return 1;
	head->next = NULL;
	adding_list(head);
	Node* head_2 = NULL;
	head_2 = (Node*)malloc(sizeof(Node));
	if (head_2 == NULL) return 1;
	head_2->next = NULL;
	adding_list(head_2);
	printf("First List\n");
	print_list(head);
	printf("Second List\n");
	print_list(head_2);
	Node* result = NULL;
	result = (Node*)malloc(sizeof(Node));
	if (result == NULL) return 1;
	result->next = NULL;
	int bool_s = 0;
	Node* tmp = head;
	Node* tmp_2 = head_2;
	while (tmp != NULL)
	{
		bool_s = 0;
		tmp_2 = head_2;
		while (tmp_2 != NULL)
		{
			if (tmp->degree == tmp_2->degree)
			{
				int value_result = tmp->value - tmp_2->value;
				push(result, value_result, tmp->degree);
				bool_s = 1;
				break;
			}
			tmp_2 = tmp_2->next;
		}
		if (bool_s == 0)
		{
			push(result, tmp->value, tmp->degree);
		}
		tmp = tmp->next;
	}
	tmp_2 = head_2;
	while (tmp_2 != NULL)
	{
		bool_s = 0;
		tmp = head;
		while (tmp != NULL)
		{
			if (tmp_2->degree == tmp->degree)
			{
				bool_s = 1;
				break;
			}
			tmp = tmp->next;
		}
		if (bool_s == 0)
		{
			int _value = tmp_2->value * (-1);
			push(result, _value, tmp_2->degree);

		}
		tmp_2 = tmp_2->next;
	}
	pop(&result);
	printf("Result List\n");
	print_list(result);
}

void push(Node* head, int _value, int _degree)
{
	Node* current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}
	current->next = (Node*)malloc(sizeof(Node));
	if (current->next == NULL)
	{
		printf("No memory access");
		exit(1);
	}
	current->next->value = _value;
	current->next->degree = _degree;
	current->next->next = NULL;
}

void print_list(Node* head)
{
	Node* current = head;
	while (current != NULL)
	{
		printf("Value = %d, degree = %d\n", current->value, current->degree);
		current = current->next;
	}
}

int pop(Node** head)
{
	int retval = -1;
	Node* next_node = NULL;
	if (*head == NULL)
	{
		return 1;
	}
	next_node = (*head)->next;
	retval = (*head)->value;
	free(*head);
	*head = next_node;
	return retval;
}

void adding_list(Node* head)
{
	int count_el = 0;
	do
	{
		printf("Count_value : ");
		scanf_s("%d", &count_el);
	} while (count_el <= 0);
	int i = 0;
	int tmp_value = 0;
	int bool_degree = 0;
	int tmp_degree = 0;
	int* arr_degree = (int*)malloc(sizeof(int) * count_el);
	while (i < count_el)
	{
		do
		{
			printf("Enter value :");
			scanf_s("%d", &tmp_value);
		} while (tmp_value == 0);
		do
		{
			printf("Enter degree :");
			bool_degree = 0;
			scanf_s("%d", &tmp_degree);
			for (int j = 0; j < i; j++)
			{
				if (tmp_degree == arr_degree[j])
				{
					bool_degree = 1;
					break;
				}
			}
			if (bool_degree != 1) arr_degree[i] = tmp_degree;
		} while (bool_degree == 1);
		if (i == 0) // if head hasn't data
		{
			head->value = tmp_value;
			head->degree = tmp_degree;
		}
		else push(head, tmp_value, tmp_degree);
		i++;
	}
	free(arr_degree);
}