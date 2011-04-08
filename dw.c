/*
 * Comp2129 Assignment 2
 * James Alexander
 * 307192962
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dw.h"

/*Global Vars including the head and curr pointers for linked list */
struct list *head;
struct list *curr;
char start_room[20];
char exit_room[20];
int player_doughnuts;
int player_milkshakes;

/*Creates the rooms via a linear linked list*/
int
createRooms(int rooms){
	struct room *new_room; //Tempoary room pointer
	char names[21];
	int scan, i, num_doughnuts, num_milkshakes, length;
	for (i = 0; i != rooms; ++i){
		new_room = malloc(sizeof(struct room));
		scan = scanf("%20s %d %d", names, &num_doughnuts, &num_milkshakes);//todo still need length?
		length = strlen(names);
		if (scan && num_doughnuts >= 0 && num_milkshakes >= 0 && length < 21) {//Input and boundary checking
			curr = malloc(sizeof(struct list));
			strcpy(new_room->name, names);
			new_room->num_doughnuts = num_doughnuts; //Creates tempoary room
			new_room->num_milkshakes = num_milkshakes;
			curr->room = new_room; //Sets curr's room to equal
			curr->next = head; //Sets next to head and then head to curr
			head = curr;
		}
		else { printf("error\n"); return 0; } 
	}
	return 1;
}

/*Returns enum type for directions, opp. refers to 2nd way direction*/
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

/*Creates and assigns doors to each room in the linked list*/
int
createDoors(int doors){
	int i, scan, num, counter;
	char room_one[21];
	char room_two[21];
	char path;
	int path_one;
	int path_two;
	struct room *linked_room_one;	//Refernces to linked rooms which are then set outside the while loop
	struct room *linked_room_two;
	counter = 0;					//ensures correct number of assignments 
	for (i = 0; i != doors; ++i){
		scan = scanf("%s %c %s", room_one, &path, room_two);
		if (scan){
			curr = head;
			while (curr){
				if (!strcmp(curr->room->name, room_one)){
					num = getPath(path, 0);
					if (curr->room->doors[num]->name != NULL){ //Check for existing door declaration combo
						printf("error\n");
						return 0;
					}
					linked_room_one = curr->room;
					path_one = getPath(path, 0);
					counter++;
				}
				if (!strcmp(curr->room->name, room_two)){
					linked_room_two = curr->room;
					path_two = getPath(path, 1);
					counter++;
				}

				curr = curr->next;
			}
			/*Set the doors*/
			linked_room_one->doors[path_one] = linked_room_two;
			linked_room_two->doors[path_two] = linked_room_one;		
		}
		else { printf("error\n"); return 0; } 
	}
	if (counter < 2*doors) { printf("error\n"); return 0; } //Door not a previously defined room
	return 1;
}

/*Simple method to print required output inbetween commands*/
void
printInfo(void){
	printf("%s %d %d %d %d\n", 
			curr->room->name, 
			curr->room->num_doughnuts, 
			curr->room->num_milkshakes, 
			player_doughnuts, 
			player_milkshakes);
}

/*Checks if current room is the exit room*/
int
checkState(void){
	if (!strcmp(curr->room->name, exit_room)){
		printInfo();
		printf("won\n");
		return 1; //returns true if you have won
	}
	return 0;
}

/*Move command takes in movement characters and sets the current room to the valid room*/
int
move (char c){
	if (player_doughnuts <= 0 || player_milkshakes <= 0){ //First checks resource amounts
		printInfo();
		printf("lost\n");
		return 0;
	}
	if (c == 'L'){
		if (curr->room->doors[LEFT]->name != NULL){
			curr->room = curr->room->doors[LEFT];	
			--player_doughnuts;
			--player_milkshakes;
			if (checkState()) { return 0; }
		}
		else { --player_doughnuts; --player_milkshakes; }
	}
	if (c == 'R'){
		if (curr->room->doors[RIGHT]->name != NULL){
			curr->room = curr->room->doors[RIGHT];
			--player_doughnuts;
			--player_milkshakes;
			if (checkState()) { return 0; }

		}
		else { --player_doughnuts; --player_milkshakes; }

	}
	if (c == 'U'){
		if (curr->room->doors[UP]->name != NULL){
			curr->room = curr->room->doors[UP];
			--player_doughnuts;
			--player_milkshakes;
		
			if (checkState()) { return 0; }

		}
		else { --player_doughnuts; --player_milkshakes; }
	}
	if (c == 'D'){
		if (curr->room->doors[DOWN]->name != NULL){
			curr->room = curr->room->doors[DOWN];
			--player_doughnuts;
			--player_milkshakes;
			if (checkState()) { return 0; }
		}
		else { --player_doughnuts; --player_milkshakes; }
	}
	return 1; //True to keep on going
}

/*Consume method eats doughnuts*/
int
consume(void){
	if (curr->room->num_doughnuts == 0){ //Check room resources first
		printf("lost\n"); return 0;
	}
	if (player_doughnuts > 2){ //Check players capacity
		printf("lost\n"); return 0;
	}
	curr->room->num_doughnuts = curr->room->num_doughnuts-1;
	++player_doughnuts;
	return 1;
}

/*Drinks milkshakes*/
int
drink(void){
	if (curr->room->num_milkshakes == 0){
		printf("lost\n"); return 0;
	}
	if (player_milkshakes > 1){
		printf("lost\n"); return 0;
	}
	curr->room->num_milkshakes = curr->room->num_milkshakes-1;
	++player_milkshakes;
	
	return 1;
}

/*This is the game initalization method and calls the creatRooms and doors functions above*/
int
game_setup(void){
	int number_rooms, number_doors, scan;

	/*Read in rooms and no of doughnuts and milkshakes*/
	scan = scanf("%d", &number_rooms);	
	if (scan) {	
		if (!createRooms(number_rooms)) { return 0; }
	}
	else { printf("error\n"); return 0; } 

	/*Read in number of doors*/
	scan = scanf("%d", &number_doors);
	if (scan) {
		if (!createDoors(number_doors)) { return 0; }
	}
	else { printf("error\n"); return(0); }

	/*Read in start and exit rooms - set start room*/
	scan = scanf("%s %s", start_room, exit_room);
	//printf("%s %s\n", start_room, exit_room);
	if (scan) {
		curr = head;
		while (curr){
			if (!strcmp(curr->room->name, start_room)){
				break; // curr now pointing at start room
			}
			curr = curr->next;
		}
	}
	else { printf("error\n"); return(0); }
	return 1; //Return true if all completed 
}


/*Game logic is defined within this method, some input checking and calling of specific game commands*/
void
run_game(){
	/*Begin game logic*/
	int scan; 
	char command;
	player_doughnuts = 0;
	player_milkshakes = 0;
	scan = scanf("\n%c", &command);
	while (scan != EOF){
		if (scan && (command == 'L' || command == 'U' || command == 'R' || command == 'D' || command == 'G' || command == 'M')){
			printInfo();//Called at the begining of each loop rather than inbetween
			if (command == 'L' || command == 'U' || command == 'R' || command == 'D'){
				//printf("%d %d\n", player_doughnuts, player_milkshakes);
				if (!move(command)) { return; }//If game state is not true return
				//printInfo();
			}
			if (command == 'G'){
				if (!consume()) { return; }
				//printInfo();
			}
			if (command == 'M'){
				if (!drink()) { return; }
				//printInfo();
			}
		
		}
		else { printf("error\n"); return; }

			scan = scanf("\n%c", &command);
	
	}
	printf("lost\n");
	return;
}

/*Free list attempts to free all allocated memory. 
 * Unforunately, there is some bizzare behaviour that means
 * not all test cases are working.
 * 
 */
void
free_list(){
		struct list *temp;
		struct list *i = head->next;
	//free(head->room);	
	free(head);	
	while ( i->next != NULL){
		temp = i->next;
		free(i->room);		
		free(i);
		i = temp;
	}
	
	if(i != head){
		free(i->room);
	}
	free(i);	
	
}

/*
void
free_list2() {
	struct list *item = head;
	while (item != NULL) {
		//delete the room
		free(item->room);
		struct list *next_item = item->next;
		//delete current)
		free(item);
		item = next_item;
	}
	free(item->room);
	free(item);
}
void
free_list3(){
	//struct list *item = true_head;
	curr = head;
	printf("THIS IS HEAD %s\n", head->room->name);
	while(curr){
		//free(item->room);
		printf("%s\n", curr->room->name);
		
		curr = curr->next;
	}
}
*/


/*Main Method*/
int
main(void) {

	if (game_setup()){ //If game setup reuturns, run the game!
		run_game();
	}

	free_list();//Free all allocated memory
	//printf("lost\n"); //scan reached EOF and not at winning room
	if (head != NULL){
			free(head);
	}
	return 0;
}
