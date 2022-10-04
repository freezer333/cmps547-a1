
#define UPQ_EVENT "event"
#define UPQ_UPDATE "update"

#define UPQ_EVENT_CODE 0
#define UPQ_UPDATE_CODE 1

#define LABEL_BUFFER_MAX 256
#define EVENT_BUFFER_MAX sizeof(double)*2 > 256 ? sizeof(double) *3 : 256

#include "list.h"


struct upq_payload {
	char category[7];  // Will always be either "event" or "update"
	char label[LABEL_BUFFER_MAX];
	char data[EVENT_BUFFER_MAX];
};

/**
 * TODO:  
 * 
 * Utility method to extract the appropriate data from the payload.  
 *
 *  - Label will be filled into the buffer (label) supplied.  The buffer
 *    shall have pre-allocated space for up to LABEL_BUFFER_MAX characters.

 *  - Category will be examined.  If the payload's category is UPQ_EVENT then
 *    string data is copied from the payload's data to the char * event buffer
 *    which shall be pre-allocaated with space for up to EVENT_BUFFER_MAX characters.
 *    If the payload's category is UPQ_UPDATE, then the positional values (three doubles)
 *    are copied into the positions array supplied (and pre-allocated for 3 doubles).

 *  - Returns either UPQ_EVENT_CODE or UPQ_UDPATE_CODE depending on category.
 */
int extract_data(struct upq_payload * payload, char * label, double * positions, char * event);


/**
 * Constructs an upq_payload with category of "event", and places
 * the payload with associated data at the end of the linked list.
 */
void put_event(struct linkedlist *queue, char * label, char * event_data);

/**
 * TODO:  
 * 
 * Constructs an upq_payload with category of "update", and places
 * the payload with associated data into the linked list according to
 * the update rules.  Updates will "bubble" up towards the front of the
 * list, and replace the earliers update with the same label - if and only
 * if the update is encountered before finding an event.
 */
void put_update(struct linkedlist *queue, char *label, double * position_data);

/**
 * TODO:  
 * 
 * Removes a single node from the linked list, and copies the data into
 * payload_buffer.
 */
void get(struct linkedlist *queue, struct upq_payload * payload_buffer);