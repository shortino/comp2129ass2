#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw.h"

struct list *head;
struct list *curr;

void 
createRooms(int rooms){
	struct room *new_room;
	char names[21];
	int scan, i, num_doughnuts, num_milkshakes, length;
	for (i = 0; i != rooms; ++i){
		new_room = malloc(sizeof(struct room));
		scan = scanf("%20s %d %d", names, &num_doughnuts, &num_milkshakes);//todo still need length?
		length = strlen(names);
		if (scan && num_doughnuts > 0 && num_milkshakes > 0 && length < 21) {
			curr = malloc(sizeof(struct list));
			strcpy(new_room->name, names);
			new_room->num_doughnuts = num_doughnuts;
			new_room->num_milkshakes = num_milkshakes;
			curr->room = new_room;
			curr->next = head;
			head = curr;
		}
		else { printf("error\n"); exit(1); } 
	}

}

enum direction getPath(char path, int opposite){
	if(opposite){
		if (path == 'L') return RIGHT;
		if (path == 'R') return LEFT;
		if (path == 'U') return DOWN;
		if (path == 'D') return UP;
	}
	if (!opposite){
		if (path == 'L') return LEFT;
		if (path == 'R') return RIGHT;
		if (path == 'U') return UP;
		if (path == 'D') return DOWN;
	}
	return 0;
}

void
createDoors(int doors){
	int i, scan, num;
	char room_one;
	char room_two;
	char path;
	char * ptr;

	for (i = 0; i != doors; ++i){
		scan = scanf("%s %c %s", &room_one, &path, &room_two);
		curr = head;
		while (curr){
			if (strcmp(curr->room->name, &room_one)){
				num = getPath(path, 0);
				if (curr->room->doors[num] != NULL){ //Check for existing door declaration combo
					printf("error\n");
					exit(1);
				}
				*ptr = room_two;
				curr->room->doors[num] =  *ptr;
				strcpy(curr->room->doors[num], curr->room->name);
			}
			if (strcmp(curr->room->name, room_two)){
				strcpy(curr->room->doors[getPath(path, 1)], room_one);
			}
			curr = curr->next;
		}
	}
}


int
main(void) {

	int number_rooms, number_dorrs, scan;
	int i;

	/*Read in rooms and no of doughnuts and milkshakes*/
	scan = scanf("%d", &number_rooms);	
	if (scan) {	
		createRooms(number_rooms);
	}
	else { printf("error\n"); exit(1); } 
	/*Read in number of doors*/
	scan = scanf("%d", &number_doors);
	if (scan) {
		createDoors(number_doors);
	}
	else { printf("error\n"); exit(1); } 
	curr = head;
	while(curr){
		printf("%s %i %i\n", curr->room->name, curr->room->num_doughnuts, curr->room->num_milkshakes);
		curr = curr->next;
	}



	
	return 0;
}
