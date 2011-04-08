#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw.h"

struct list *head;
struct list *curr;
char start_room[20];
char exit_room[20];
int player_doughnuts;
int player_milkshakes;

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
	int i, scan, num, counter;
	char room_one[21];
	char room_two[21];
	char path;
	int path_one;
	int path_two;
	struct room *linked_room_one;
	struct room *linked_room_two;
	counter = 0;
	for (i = 0; i != doors; ++i){
		scan = scanf("%s %c %s", room_one, &path, room_two);
		if (scan){
			//printf("this is rm one and two %s %s\n", room_one, room_two);
			curr = head;
			while (curr){
				if (!strcmp(curr->room->name, room_one)){
					num = getPath(path, 0);
					if (curr->room->doors[num]->name != NULL){ //Check for existing door declaration combo
						printf("error\n");
						exit(1);
					}
					linked_room_one = curr->room;
					path_one = getPath(path, 0);
					counter++;
					//printf("room oned %s\n", linked_room_one->name);
				}
				if (!strcmp(curr->room->name, room_two)){
					linked_room_two = curr->room;
					path_two = getPath(path, 1);
					counter++;
					//printf("room two is here after set %s\n", curr->room->name);
				}

				curr = curr->next;
			}
			/*Set the doors*/
			linked_room_one->doors[path_one] = linked_room_two;
			//printf("room one %s\n", linked_room_one->doors[path_one]->name);
			linked_room_two->doors[path_two] = linked_room_one;		
			//printf("room two %s\n", linked_room_two->doors[path_two]->name);
		}
		else { printf("error\n"); exit(1); } 
	}
	if (counter < 2*doors) { printf("error\n"); exit(1); } //Door not previously defined room
	curr = head;
	while (curr){
		int j;
		for (j = 0; j != 4; ++j){
			if (curr->room->doors[j]->name != NULL) printf("%s %s %d\n",curr->room->name,  curr->room->doors[j]->name, j );
		}
		curr = curr->next;
	}
}




void
printInfo(void){
	printf("%s %d %d %d %d\n", 
			curr->room->name, 
			curr->room->num_doughnuts, 
			curr->room->num_milkshakes, 
			player_doughnuts, 
			player_milkshakes);
}

void
checkState(void){
	if (!strcmp(curr->room->name, exit_room)){
		printInfo();
		printf("won\n");
		exit(1);
	}
}

void
move (char c){
	if (player_doughnuts == 0 && player_milkshakes == 0){
		printf("lost\n");
		exit(1);
	}
	if (c == 'L'){
		if (curr->room->doors[LEFT]->name != NULL){
			curr->room = curr->room->doors[LEFT];
			player_doughnuts = player_doughnuts-1;
			--player_milkshakes;
			printf("%d %d\n", player_doughnuts, player_milkshakes);
			checkState();
		}
	}
	if (c == 'R'){
		if (curr->room->doors[RIGHT]->name != NULL){
			curr->room = curr->room->doors[RIGHT];
			--player_doughnuts;
			--player_milkshakes;
			checkState();
		}
	}
	if (c == 'U'){
		if (curr->room->doors[UP]->name != NULL){
			curr->room = curr->room->doors[UP];
			--player_doughnuts;
			--player_milkshakes;
			checkState();

		}
	}

	if (c == 'D'){
		if (curr->room->doors[DOWN]->name != NULL){
			curr->room = curr->room->doors[DOWN];
			--player_doughnuts;
			--player_milkshakes;
			checkState();
		}
	}
	--player_doughnuts;
	--player_milkshakes;
}

void
consume(void){
	if (curr->room->num_doughnuts == 0){
		printf("lost\n"); exit(1);
	}
	if (player_doughnuts > 2){
		printf("lost\n"); exit(1);
	}
	curr->room->num_doughnuts = curr->room->num_doughnuts-1;
	++player_doughnuts;
}


void
drink(void){
	if (curr->room->num_milkshakes == 0){
		printf("lost\n"); exit(1);
	}
	if (player_milkshakes > 1){
		printf("lost\n"); exit(1);
	}
	curr->room->num_milkshakes = curr->room->num_milkshakes-1;
	++player_milkshakes;
}

int
main(void) {

	int number_rooms, number_doors, scan;

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

	/*Read in start and exit rooms - set start room*/
	scan = scanf("%s %s", start_room, exit_room);
	//printf("%s %s\n", start_room, exit_room);
	if (scan) {
		curr = head;
		while (curr){
			if (!strcmp(curr->room->name, start_room)){
				printf("setted start rm\n");
				break; // curr now pointing at start room
			}
			curr = curr->next;
		}
	}
	else { printf("error\n"); exit(1); }

	/*Begin game logic*/
	char command;
	player_doughnuts = 0;
	player_milkshakes = 0;
	scan = scanf("%s", &command);//WHY!
	//printf("stuff %c\n", command);
		printInfo();
		while (scan != EOF){
			if (scan && (command == 'L' || command == 'U' || command == 'R' || command == 'D' || command == 'G' || command == 'M')){
				
				if (command == 'L' || command == 'U' || command == 'R' || command == 'D'){
					move(command);
					printInfo();
				}
				if (command == 'G'){
					consume();
					printInfo();
				}
				if (command == 'M'){
					drink();
					printInfo();
				}
				scan = scanf("%s", &command);
				//else { printf("error\n"); exit(1); }
			}
		else { printf("error\n"); exit(1); }
		}

		curr = head;
		while(curr){
			printf("Printing name, doughnuts, milkshakes\n");
			printf("%s %i %i\n", curr->room->name, curr->room->num_doughnuts, curr->room->num_milkshakes);
			curr = curr->next;
		}


		printf("lost\n"); //scan reached EOF and not at winning room
		return 0;
	}
