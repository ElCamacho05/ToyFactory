#ifndef WORLD_H
#define WORLD_H

typedef struct Element { // list of elements
    int drawId;
    double angle;
    struct element *next;
} ELEMENT;

typedef struct Tile { // for the tile array
    int position[2];
    ELEMENT *elementList;
}TILE;

// ROOM wrapper for graphs
typedef struct Room ROOM;
typedef struct connection {
    ROOM *contRoom;
    struct connection *nextRoom;
} CONNECTION;

typedef struct Room { // a graph of room
    int id;
    TILE *tileArray;
    CONNECTION *sideRooms; // contiguous room
} ROOM;

extern ELEMENT *phantom;

extern ROOM *MFcore;
extern ROOM *MFhead;
extern ROOM *MFarms;
extern ROOM *MFlegs;
extern ROOM *MFback;
extern ROOM *MFtool;

#endif