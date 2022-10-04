#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void linkedlist_init(struct linkedlist * list, unsigned int payload_size) {
	list->head = NULL;
	list->tail = NULL;
	list->payload_size = payload_size;
}

int linkedlist_is_empty(struct linkedlist *list) {
	return list->head == NULL ? 1 : 0;
}

void linkedlist_push(struct linkedlist *list, void * data) {
	struct node * new_node = malloc(sizeof(struct node));
	new_node->payload = malloc(list->payload_size);
	memcpy(new_node->payload, data, list->payload_size);
	if(linkedlist_is_empty(list)) {
		new_node->next = NULL;
		new_node->prev = NULL;
		list->head = new_node;
		list->tail = new_node;
	} else {
		new_node->next = NULL;
		new_node->prev = list->tail;
		list->tail->next = new_node;
		list->tail = new_node;
	}
}

int linkedlist_pop(struct linkedlist *list, void * removed) {
	if (linkedlist_is_empty(list)) {
		return 0;
	}

	struct node * to_delete = list->tail;
	list->tail = to_delete->prev;
	if (list->tail == NULL) {
		list->head = NULL;
	}
	memcpy(removed, to_delete->payload, list->payload_size);
	free(to_delete->payload);
	free(to_delete);
	return 1;
}


/* TODO:  pop_front removes a node (and copies into removed) from the front
          of the list.  Make sure you free memory that needs to be freed!
*/
int linkedlist_pop_front(struct linkedlist *list, void * removed) {
	return -1;
}

void linkedlist_print(struct linkedlist *list, void (*printer)(void *)) {
	struct node * current = list->head;
	while (current != NULL) {
		printer(current->payload);
		current = current->next;
	}
}
