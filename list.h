#ifndef LINKED_LIST
#define LINKED_LIST

struct linkedlist {
	unsigned int payload_size;
	struct node *head;
	struct node *tail;
};

struct node {
	struct node * next;
	struct node * prev;
	void * payload;
};

void linkedlist_init(struct linkedlist * list, unsigned int payload_size);
int linkedlist_is_empty(struct linkedlist *list) ;
void linkedlist_push(struct linkedlist *list, void * data) ;
int linkedlist_pop(struct linkedlist *list, void * removed) ;
int linkedlist_pop_front(struct linkedlist *list, void * removed) ;
void linkedlist_print(struct linkedlist *list, void (*printer)(void *)) ;

#endif