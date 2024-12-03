#include <stdio.h>
#include <stdlib.h>

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s {
	LINKED_LIST_NODE next;
	void *data;
} LINKED_LIST_NODE_t[1];

typedef struct {
	LINKED_LIST_NODE head;
} LINKED_LIST_t[1], *LINKED_LIST;

LINKED_LIST linked_list_init(){
	LINKED_LIST list = (LINKED_LIST)malloc(sizeof(LINKED_LIST_t));
	list->head = NULL;
	return list;
}

void linked_list_append(LINKED_LIST list, void *data) {
	LINKED_LIST_NODE node, new;
	new = (LINKED_LIST_NODE) malloc(sizeof(LINKED_LIST_NODE_t));
	new->data = data;
	new->next = NULL;
	node = (LINKED_LIST_NODE)list;
	while (node->next != NULL) {
		node = node->next;
	}
	node->next = new;
}

void linked_list_print(LINKED_LIST list) {
	LINKED_LIST_NODE node = list->head;
	while(node != NULL) {
		printf("%d ", *(int *)node->data);
		node = node->next;
	}
}

