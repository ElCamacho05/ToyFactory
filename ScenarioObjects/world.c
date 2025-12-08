
#include "world.h"
# include <stdlib.h>

ELEMENT *phantom = NULL;


void *setupPhantomElement() {
    if (phantom) return;

    phantom = (ELEMENT*) malloc(sizeof(ELEMENT));
    phantom->drawId = -1;
    phantom->angle = 0;
    phantom->next = NULL;
}

// Creates a Tile (1x1 space) for the map
TILE *createTile(double position[]) {
    TILE *tile = (TILE*) malloc(sizeof(TILE));

    tile->position[0] = position[0];
    tile->position[1] = position[1];
    tile->elementList = NULL;
    
    return tile;
}

// Create a single element initialized with an object to draw
ELEMENT *createElement(int idElem, double angle) {
    ELEMENT *elem = (ELEMENT*) malloc(sizeof(ELEMENT));
    
    elem->drawId = idElem;
    elem->angle = angle;
    elem->next = NULL;

    return elem;
}

// Stack an Element into the Tile,
// so the drawing could be easy by simply visiting all the nodes in the tile
// each layer will also be 1 x 0.25 x 1 size
// Phantom layers will be signed with a -1 ID
void insertElement(TILE **tile, ELEMENT *elem) {
    if (!elem) return;

    elem->next = (*tile)->elementList;
    (*tile)->elementList = elem;
}

// Pops the last element of the Tile's Element list
ELEMENT *popElement(TILE **tile) {
    ELEMENT *elem = (*tile)->elementList;
    if (!elem) return NULL;

    (*tile)->elementList = (*tile)->elementList->next;
    elem->next = NULL;

    return elem;
}

// Deletes de whole stack of elements in the tile
// essential for changing maps or rooms
void deleteElementsInTile(TILE **tile) {
    ELEMENT *temp = (*tile)->elementList;
    ELEMENT *delete;

    while (temp) {
        delete = temp;
        temp = temp->next;
        free(delete);
    }
}

// create a WxD array of Tiles
TILE *createTileMap(int width, int depth) {
    int size = (width+1)*(depth+1);
    TILE *tiles = (TILE *) malloc(sizeof(TILE)*size);
    TILE *temp;

    // initialize positions
    for (int i = -width; i < width; i++) {
        for (int j = -depth; j < width; j++) {
            temp->elementList = NULL;
            temp->position[0] = i;
            temp->position[1] = j;
            temp++; // change to item in array
        }
    }

    return tiles;
}

// deletes the whole tile, by deleting the elements into it,
// and then deleting the tile itself (SELF DESTRUCTION IN 3 2 1...)
void deleteMapTile(TILE *tileArray) {
    free(tileArray);
}

CONNECTION *createConnection(ROOM *room) {
    CONNECTION *conn = (CONNECTION *) malloc(sizeof(CONNECTION));
    conn->contRoom = room;
    conn->nextRoom = NULL;

    return conn;
}

void linkRooms(ROOM *room1, ROOM *room2) {
    // one direction (XD)
    CONNECTION *newConn1 = createConnection(room2);
    if (!newConn1) return; 
    newConn1->contRoom = room1->sideRooms;
    room1->sideRooms = newConn1;

    // other direction
    CONNECTION *newConn2 = createConnection(room1);
    if (!newConn2) return;
    newConn2->contRoom = room2->sideRooms;
    room2->sideRooms = newConn2;
}

void deleteConnections(ROOM *room) {
    CONNECTION *temp = room->sideRooms;
    CONNECTION *delete;
    while (temp) {
        delete = temp;
        temp = temp->nextRoom;
        free(delete);
    }
}

ROOM *createRoom(int id, int width, int depth) {
    ROOM *newRoom = (ROOM *) malloc(sizeof(ROOM));

    if (!newRoom) return NULL;
    newRoom->id = id;
    newRoom->tileArray = createTileMap(width, depth);
    newRoom->sideRooms = NULL;

    return newRoom;
}

void setupMapFactory() {

}

void mapFactory() {

}