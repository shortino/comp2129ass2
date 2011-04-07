#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw.h"

struct list *head;

void 
createRooms(int rooms){
	struct list *curr;
	struct room *new_room;
	char names[21];
	int scan, i, num_doughnuts, num_milkshakes, length;

	for (i = 0; i != rooms; ++i){
	
		new_room = malloc(sizeof(struct room));
		scan = scanf("%20s %d %d", names, &num_doughnuts, &num_milkshakes);
		length = strlen(names);
		if (scan && num_doughnuts > 0 && num_milkshakes > 0 && length < 21) {
			curr = malloc(sizeof(struct list));
			strcpy(new_room->name, names);
			//new_room->name = names;
			new_room->num_doughnuts = num_doughnuts;
			new_room->num_milkshakes = num_milkshakes;
			curr->room = new_room;
			curr->next = head;
			head = curr;
		}
		else { printf("error\n"); exit(1); } 
	}
	curr = head;
	while(curr){
		printf("%s %i %i\n", curr->room->name, curr->room->num_doughnuts, curr->room->num_milkshakes);
		curr = curr->next;
	}
}


int
main(void) {

	int number_rooms, scan;
	int i;

	/*Read in rooms and no of doughnuts and milkshakes*/
	scan = scanf("%d", &number_rooms);	
	if (scan){	
		createRooms(number_rooms);
		printf("this is %d\n", scan);
	}
	else { printf("error\n"); exit(1); } 



	
	return 0;
}
