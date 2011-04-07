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
	char name[21];
	int scan, i, num_doughnuts, num_milkshakes, length;

	for (i = 0; i != rooms; ++i){
		scan = scanf("%c %d %d", name, &num_doughnuts, &num_milkshakes);
		length = strlen(name);
		if (scan && num_doughnuts > 0 && num_milkshakes > 0 && length < 21) {
			curr = malloc(sizeof(struct list));
			new_room = malloc(sizeof(struct room));
			new_room->name = name;
			new_room->num_doughnuts = num_doughnuts;
			new_room->num_milkshakes = num_milkshakes;
			curr->room = new_room;
			curr->next = head;
			head = curr;
		}
		else { printf("error\n"); exit(1); } 
	}
}




int
main(void) {

	int number_rooms, scan;
	int i;

	/*Read in rooms and no of doughnuts and milkshakes*/
	scan = scanf("%d", &number_ooms);	
	if (scan){	
		createRooms(number_rooms);
		printf("this is %d\n", scan);
	}
	else { printf("error\n"); exit(1); } 



	
	return 0;
}
