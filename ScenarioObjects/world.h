#ifndef WORLD_H
#define WORLD_H

typedef struct Element { // list of elements
    int drawId;
    double angle;
    struct Element *next;
} ELEMENT;

typedef struct Tile { // for the tile array
    float position[2];
    int texture;
    ELEMENT *head;
    ELEMENT *tail;
} TILE;

// ROOM wrapper for graphs
typedef struct Room ROOM;
typedef struct connection {
    ROOM *contRoom;
    struct connection *nextRoom;
} CONNECTION;

typedef struct Room { // a graph of room
    int id;
    TILE **tileArray;
    int width;
    int depth;
    CONNECTION *sideRooms; // contiguous room
} ROOM;

typedef struct Map {
    ROOM *initialRoom;
} MAP;

extern ELEMENT *phantom;

extern MAP *test;
extern MAP *factory;
extern ROOM *firstRoom;

void setupPhantomElement();
TILE *createTile(float position[]);
ELEMENT *createElement(int idElem, double angle);
void insertElement(TILE **tile, ELEMENT *elem);
ELEMENT *popElement(TILE **tile);
void deleteElementsInTile(TILE **tile);
TILE **createTileMap(int width, int depth);
void freeTileMap(TILE **tiles, int width, int depth);
CONNECTION *createConnection(ROOM *room);
void linkRooms(ROOM *room1, ROOM *room2);
void deleteConnections(ROOM *room);
ROOM *createRoom(int id, int width, int depth);
ROOM *getRoom(int id, ROOM *room);
void place(ROOM *room, int elemID, float angle, float posX, float posZ);
void setupMapTest();
void setupMapFactory();

#endif