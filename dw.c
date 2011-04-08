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
	char room_one[21];
	char room_two[21];
	char path;
	int path_one;
	int path_two;
	struct room *linked_room_one;
	struct room *linked_room_two;

	for (i = 0; i != doors; ++i){
		//linked_room_one = malloc(sizeof(struct room));

		//curr = malloc(sizeof(struct list));
		scan = scanf("%s %c %s", room_one, &path, room_two);
		printf("this is rm one and two %s %s\n", room_one, room_two);
		linked_room_two = NULL;
		curr = head;
		while (curr){
			if (!strcmp(curr->room->name, room_one)){
				num = getPath(path, 0);
				//printf("room one %s\n", room_one);
				if (curr->room->doors[num]->name != NULL){ //Check for existing door declaration combo
					printf("error\n");
					exit(1);
				}
				linked_room_one = curr->room;
				path_one = getPath(path, 0);
				//printf("room oned %s\n", linked_room_one->name);
				//strcpy(curr->room->doors[num], curr->room->name);
			}
			if (!strcmp(curr->room->name, room_two)){
				printf("%d\n", strcmp(curr->room->name, room_two));
				//linked_room_two = malloc(sizeof(struct room));
				//strcpy(curr->room->doors[getPath(path, 1)], room_one);
				linked_room_two = NULL;
				linked_room_two = curr->room;
				path_two = getPath(path, 1);
				printf("room two is here after set %s\n", curr->room->name);
			}

			curr = curr->next;
		}
		/*Set the doors*/
		/*
		curr = head;
		while(curr){
			if (strcmp(curr->room->name, room_one)){
				curr->room->doors[path_one] = linked_room_two;
			}
			if (strcmp(curr->room->name, room_two)){
				curr->room->doors[path_two] = linked_room_one;
			}
		
		curr = curr->next;
		}
		*/
		linked_room_one->doors[path_one] = linked_room_two;
		//printf("path one and two %d %d\n", path_one, path_two);
		//printf("room one %s\n", linked_room_one->doors[path_one]->name);
		linked_room_two->doors[path_two] = linked_room_one;		
		//printf("room two %s\n", linked_room_two->doors[path_two]->name);
		
	}
	curr = head;
	while (curr){
		int j;
		for (j = 0; j != 4; ++j){
			if (curr->room->doors[j]->name != NULL) printf("%s %s %d\n",curr->room->name,  curr->room->doors[j]->name, j );
		}
		curr = curr->next;
	}
}


int
main(void) {

	int number_rooms, number_doors, scan;
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
