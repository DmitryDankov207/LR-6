#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define STACK_OVERFLOW -100

typedef int T;
typedef struct Stack {
	T value;
	size_t tree;
	struct Stack *next;
} Node_s;

void push_s(Node_s **head, T value, size_t tree) {
	Node_s *tmp = (Node_s*)malloc(sizeof(Node_s));
	if (tmp == NULL)
		exit(STACK_OVERFLOW);
	tmp->next = *head;
	tmp->value = value;
	tmp->tree = tree;
	*head = tmp;
}

void printStack(const Node_s *head) {
	printf_s("\n");
	while (head) {
		printf_s("\nvalue : %d\ntree : %d ", head->value, head->tree);
		head = head->next;
	}
}

void generateStack(Node_s **head, size_t values, size_t trees) {
	size_t tree;
	for (size_t i = 0; i < values; i++) {
		if (i < trees)
			tree = i;
		else
			tree = rand() % trees;
		push_s(head, -500 + rand() % 1000, tree);
	}
}

typedef struct Tree {
	T value;
	struct Tree *left;
	struct Tree *right;
	struct Tree *parent;
} Node_t;

Node_t* getFreeNode(T value, Node_t *parent) {
	Node_t* tmp = (Node_t*)malloc(sizeof(Node_t));
	tmp->left = tmp->right = NULL;
	tmp->value = value;
	tmp->parent = parent;
	return tmp;
}

void push_t(Node_t **head, T value) {
	if (*head == NULL)
		*head = getFreeNode(value, NULL);
	else {
		Node_t *tmp = *head;
		while (tmp) {
			if (value >= tmp->value)
				if (tmp->right)
					tmp = tmp->right;
				else {
					tmp->right = getFreeNode(value, tmp);
					return;
				}
			else if (value < tmp->value)
				if (tmp->left)
					tmp = tmp->left;
				else {
					tmp->left = getFreeNode(value, tmp);
					return;
				}
		}
	}
}

void findSum(Node_t* root, T *sum) {
	if (root) {
		(*sum) += root->value;
		findSum(root->left, sum);
		findSum(root->right, sum);
	}
}

Node_t** createTrees(const Node_s *head, size_t treeCount) {
	Node_t **trees = (Node_t**)malloc(sizeof(Node_t) * treeCount);
	for (size_t i = 0; i < treeCount; i++)
		trees[i] = NULL;
	while (head) {
		push_t(&(trees[head->tree]), head->value);
		head = head->next;
	}
	return trees;
}

void findSums(Node_t **trees, size_t treeCount) {
	T sum;
	for (size_t i = 0; i < treeCount; i++) {
		sum = 0;
		findSum(trees[i], &sum);
		printf_s("\nsum of tree[%d] = %d", i, sum);
	}
}

void completeTask() {
	Node_s *stack = NULL;
	size_t valueCount, treeCount;
	scanf_s("%d", &valueCount);
	scanf_s("%d", &treeCount);
	generateStack(&stack, valueCount, treeCount);
	printStack(stack);
	Node_t **trees = createTrees(stack, treeCount);
	findSums(trees, treeCount);
	for (size_t i = 0; i < treeCount; i++)
		free(trees[i]);
	free(stack);
	free(trees);
}

int main() {
	completeTask();
	_getch();
	return 0;
}