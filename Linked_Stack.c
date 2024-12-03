#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct LINKED_STACK_NODE_s *LINKED_STACK_NODE;
typedef struct LINKED_STACK_NODE_s {
	LINKED_STACK_NODE next;
	void *data;
} LINKED_STACK_NODE_t[1];

typedef struct LINKED_STACK_s {
	LINKED_STACK_NODE head;
} LINKED_STACK_t[1], *LINKED_STACK;

int linked_stack_is_empty(LINKED_STACK stack) {
	return stack->head == NULL;
}

LINKED_STACK linked_stack_init() {
	LINKED_STACK stack = malloc(sizeof(LINKED_STACK_t));
	stack->head = NULL;
	return stack;
}

void linked_stack_push(LINKED_STACK stack, void *data) {
	LINKED_STACK_NODE new = malloc(sizeof(LINKED_STACK_NODE_t));
	if (new != NULL) {
		new->data = data;
		new->next = stack->head;
		stack->head = new;
	} else {
		printf("Memory allocation error!\n");
		exit(0);
	}
}

void *linked_stack_pop(LINKED_STACK stack) {
	LINKED_STACK_NODE temp;
	void *result = NULL;
	if (stack->head != NULL) {
		temp = stack->head;
		stack->head = temp->next;
		result = temp->data;
		free(temp);
	} else {
		printf("Stack is empty\n");
		exit(0);
	}
	return result;
}

void linked_stack_free(LINKED_STACK stack) {
	while (stack->head != NULL) {
		linked_stack_pop(stack);
	}
	free(stack);
}

