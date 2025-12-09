#ifndef WORLD_H
#define WORLD_H

#include <GL/glut.h>

typedef struct Element { // list of elements
    GLuint *drawId;
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
    int visited; // because its a bidirectional graph, we dont want to visit it again
    CONNECTION *sideRooms; // contiguous room
} ROOM;

typedef struct Map {
    ROOM *initialRoom;
} MAP;

typedef struct RoomPileNode {
    ROOM *room;
    struct RoomPileNode *next;
} ROOM_P_N;

typedef struct RoomPile {
    ROOM_P_N *head;
    int size;
} ROOM_P;

extern ELEMENT *phantom;

extern MAP *test;
extern MAP *factory;
extern ROOM *firstRoom;

// void setupPhantomElement();
TILE *createTile(float position[]);
ELEMENT *createElement(int *idElem, double angle);
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
float getTreeWidth(ROOM *room, float xGap);
void resetGraphFlags(ROOM *room);
void place(ROOM *room, int *elemID, float angle, float posX, float posZ);
void setupMapTest();
void setupMapFactory();

#endif