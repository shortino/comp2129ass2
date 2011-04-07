#ifndef DW_H_
#define DW_H_

// for directions for door placement in a room. 
enum direction {UP=0, RIGHT=1, DOWN=2, LEFT=3};

// data structure to store information about a room. 
struct room {
  char name[21];          // name of the room 
  int num_doughnuts;      // number of doughnuts in the room
  int num_milkshakes;     // number of milkshakes in the room
  struct room *doors[4];  // doors of the room for each direction
                          //  doors[LEFT] -> left door
                          //  doors[RIGHT] -> right door
                          //  doors[UP] -> door up 
                          //  doors[DOWN] -> door down
}; 

// data structure is a singly-linked list to store all rooms.
struct list {
  struct room *room;   // pointer to room 
  struct list *next;   // next node in the list   
};

#endif
