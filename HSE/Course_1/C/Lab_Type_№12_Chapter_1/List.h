#pragma once

typedef struct Node {
	int value; // rate
	int degree;
	struct Node* next;
} Node;
