
#include "upq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * TODO
 * Tip:  strncpy will be good for copying label and event data, but
 *       you will want to use memcpy to extract update positions.
 */
int extract_data(struct upq_payload * payload, char * label, double * positions, char * event) {
	return -1;
}

/**
 * The simplest case is handled for you, here we create
 * a payload and add it to the linked list.
 */
void put_event(struct linkedlist *queue, char * label, char * event_data) {
	struct upq_payload up;
	strcpy(up.category, UPQ_EVENT);
	strncpy(up.label, label, LABEL_BUFFER_MAX);
	strncpy(up.data, event_data, EVENT_BUFFER_MAX);
	linkedlist_push(queue, &up);
	return;
}

/**
 * TODO:  
 * 
 * This is the most difficult part of the implementation.
 * Make sure you are handling the case where the linked list
 * is currently empty.
 * 
 * If you find a matching update that will be replaced, also
 * make sure that you free the memory associated with the node.
 * 
 * You will need to access the linked list's tail, and iterate
 * forward using the prev pointer.
 * 
 * - If the list is empty, add the update to the end.
 * - Starting at tail, iterate forward towards head:
 *   - If you find an event, then add the update to the end and return.
 *   - If you find an update with a matching label, before you find an event, 
 *     replace the node's data with this update payload.
 *   - If you reach the head of the list, and neither found a matching
 *     update nor an event, then add the payload to the end of the list.
 * 
 */
void put_update(struct linkedlist *queue, char *label, double * position_data) {
	
}

/**
 * TODO:  
 * 
 * Don't over complicate this... remember that the pop_front function
 * in the linkedlist MUST be implemented (see list.c), and it should 
 * be taking care of most of the work here...
 */
void get(struct linkedlist *queue, struct upq_payload * payload_buffer) {
	
}