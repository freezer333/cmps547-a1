#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "upq.h"

/* This is likely helpful for debugging, it can be used
   with the linkedlist_print function.
*/
void print(void * dtptr) {
	struct upq_payload * d = (struct upq_payload *) dtptr;
	fprintf(stderr, "%s, %s", d->category, d->label);
	if (strcmp(d->category, UPQ_EVENT) == 0) {
		char * event_data = (char * ) d->data;
		fprintf(stderr, ", %s\n", event_data);
	} else {
		double * positions = (double *) d->data;
		fprintf(stderr, ", (%f, %f, %f)\n", positions[0], positions[1], positions[2]);
	}
}

void test_case_1() {
	struct linkedlist upq;
	struct upq_payload up;
	char label_buff[LABEL_BUFFER_MAX];
	char event_buff[EVENT_BUFFER_MAX];
	double position_buff[3];
	int c;

	linkedlist_init(&upq, sizeof(struct upq_payload));

	put_event(&upq, "APP", "START");
	get(&upq, &up);

	assert(strcmp(up.category, UPQ_EVENT) == 0);
	assert(strncmp(up.label, "APP", LABEL_BUFFER_MAX) == 0);
	assert(strncmp(up.data, "START", EVENT_BUFFER_MAX) == 0);
	
	c  =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 0);
	assert(strncmp(label_buff, "APP", LABEL_BUFFER_MAX) == 0);
	assert(strncmp(event_buff, "START", EVENT_BUFFER_MAX) == 0);
}

void test_case_2() {
	struct linkedlist upq;
	struct upq_payload up;
	char label_buff[LABEL_BUFFER_MAX];
	char event_buff[EVENT_BUFFER_MAX];
	double position_buff[3];
	int c;

	linkedlist_init(&upq, sizeof(struct upq_payload));

	put_event(&upq, "APP", "START");
	position_buff[0] = position_buff[1] = position_buff[2] = 1.0;
	put_update(&upq, "PLAYER 1", position_buff);
	position_buff[0] = position_buff[1] = position_buff[2] = 1.1;
	put_update(&upq, "PLAYER 1", position_buff);
	put_event(&upq, "APP", "COLLISION");
	position_buff[0] = position_buff[1] = position_buff[2] = 0.9;
	put_update(&upq, "PLAYER 1", position_buff);

	// Should still have the start event
	get(&upq, &up);
	c =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 0);
	assert(strncmp(label_buff, "APP", LABEL_BUFFER_MAX) == 0);
	assert(strncmp(event_buff, "START", EVENT_BUFFER_MAX) == 0);

	// The position update should only include the 1.1, since the 1.0 should
	// be overwritten
	get(&upq, &up);
	c =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 1);
	assert(strncmp(label_buff, "PLAYER 1", LABEL_BUFFER_MAX) == 0);
	assert(position_buff[0] == 1.1);

	// The next item on queue should be the collision
	get(&upq, &up);
	c =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 0);
	assert(strncmp(label_buff, "APP", LABEL_BUFFER_MAX) == 0);
	assert(strncmp(event_buff, "COLLISION", EVENT_BUFFER_MAX) == 0);

	// The position update should be the final update posted.
	get(&upq, &up);
	c =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 1);
	assert(strncmp(label_buff, "PLAYER 1", LABEL_BUFFER_MAX) == 0);
	assert(position_buff[0] == 0.9);
}

void test_case_3() {
	struct linkedlist upq;
	struct upq_payload up;
	char label_buff[LABEL_BUFFER_MAX];
	char event_buff[EVENT_BUFFER_MAX];
	double position_buff[3];
	int c;

	linkedlist_init(&upq, sizeof(struct upq_payload));

	put_event(&upq, "APP", "START");
	
	position_buff[0] = position_buff[1] = position_buff[2] = 1.0;
	put_update(&upq, "PLAYER 1", position_buff);
	
	position_buff[0] = position_buff[1] = position_buff[2] = 5;
	put_update(&upq, "PLAYER 2", position_buff);

	position_buff[0] = position_buff[1] = position_buff[2] = 1.1;
	put_update(&upq, "PLAYER 1", position_buff);
	
	position_buff[0] = position_buff[1] = position_buff[2] = 0.9;
	put_update(&upq, "PLAYER 1", position_buff);

	// Remove APP Start
	get(&upq, &up);
	// Remove Player 1 update that was collecting the previous updates
	get(&upq, &up);
	
	// This should now be the update for player 1 on record
	position_buff[0] = position_buff[1] = position_buff[2] = 0.8;
	put_update(&upq, "PLAYER 1", position_buff);

	get(&upq, &up);
	c =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 1);
	assert(strncmp(label_buff, "PLAYER 2", LABEL_BUFFER_MAX) == 0);
	assert(position_buff[0] == 5);

	get(&upq, &up);
	c =extract_data(&up, label_buff, position_buff, event_buff);
	assert(c == 1);
	assert(strncmp(label_buff, "PLAYER 1", LABEL_BUFFER_MAX) == 0);
	assert(position_buff[0] == 0.8);

	assert(linkedlist_is_empty(&upq) == 1);
}


/******************************************************
 * 
 * These test cases simulate an updateable queue supporting
 * position data in a multiplayer game, with events such
 * as application start, and player collisions.  Your 
 * updateable queue of course should support any type
 * of event and update labels, 
 * 
 * ***************************************************/
int main() {

	// When run, if there is no output, and no assertion errors, then you win!
	test_case_1();
	test_case_2();
	test_case_3();

	// You are encouraged to add more test cases (I will, when testing your code).
}

