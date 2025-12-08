
#include "world.h"
#include "scenario.h"
# include <stdlib.h>
#include <stdio.h>

ELEMENT *phantom = NULL;

MAP *test = NULL;
MAP *factory = NULL;

// ROOM *MFcore;
// ROOM *MFhead;
// ROOM *MFarms;
// ROOM *MFlegs;
// ROOM *MFback;
// ROOM *MFtool;

void setupPhantomElement() {
    if (phantom) return;

    phantom = (ELEMENT*) malloc(sizeof(ELEMENT));
    phantom->drawId = -1;
    phantom->angle = 0;
    phantom->next = NULL;
}

// Creates a Tile (1x1 space) for the map
TILE *createTile(float position[]) {
    TILE *tile = (TILE*) malloc(sizeof(TILE));

    tile->position[0] = position[0];
    tile->position[1] = position[1];
    tile->head = NULL;
    tile->tail = NULL;
    
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

// Queue an Element into the Tile,
// so the drawing could be easy by simply visiting all the nodes in the tile
// each layer will also be 1 x 0.25 x 1 size
// Phantom layers will be signed with a -1 ID
void insertElement(TILE **tile, ELEMENT *elem) {
    if (!elem || !tile || !*tile) return;

    elem->next = NULL;

    if ((*tile)->head == NULL) {
        (*tile)->head = elem;
        (*tile)->tail = elem;
    } else {
        (*tile)->tail->next = elem;
        (*tile)->tail = elem;
    }
}

// Pops the first element of the Tile's Element list
ELEMENT *popElement(TILE **tile) {
    if (!tile || !*tile || !(*tile)->head) return NULL;

    ELEMENT *elem = (*tile)->head;
    
    (*tile)->head = (*tile)->head->next;
    
    if ((*tile)->head == NULL) {
        (*tile)->tail = NULL;
    }

    elem->next = NULL;

    return elem;
}

// Deletes de whole stack of elements in the tile
// essential for changing maps or rooms
void deleteElementsInTile(TILE **tile) {
    ELEMENT *temp = (*tile)->head;
    ELEMENT *delete;

    while (temp) {
        delete = temp;
        temp = temp->next;
        free(delete);
    }
    (*tile)->head = NULL;
    (*tile)->tail = NULL;
}

// create a WxD array of Tiles
TILE **createTileMap(int width, int depth) {
    int size = (2*width+1)*(2*depth+1); // last one is NULL
    TILE **tiles = (TILE **) malloc(sizeof(TILE *)*size);
    int idx = 0;
    float position[2];

    // initialize positions
    for (int i = -width; i <= width; i++) {
        for (int j = -depth; j <= depth; j++) {
            position[0] = i;
            position[1] = j;
            tiles[idx] = createTile(position);
            tiles[idx]->texture = -1;
            tiles[idx]->head = NULL;
            tiles[idx]->tail = NULL;
            tiles[idx]->position[0] = i;
            tiles[idx]->position[1] = j;
            idx++;
        }
    }

    return tiles;
}

// deletes the whole tile, by deleting the elements into it,
// and then deleting the tile itself (SELF DESTRUCTION IN 3 2 1...)
void freeTileMap(TILE **tiles, int width, int depth) {
    int size = (2 * width + 1) * (2 * depth + 1);
    
    for (int i = 0; i < size; i++) {
        deleteElementsInTile(&tiles[i]);
        free(tiles[i]); 
    }
    
    free(tiles);
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
    newConn1->contRoom = room1;
    room1->sideRooms = newConn1;

    // other direction
    CONNECTION *newConn2 = createConnection(room1);
    if (!newConn2) return;
    newConn2->contRoom = room2;
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
    newRoom->width = width;
    newRoom->depth = depth;
    newRoom->tileArray = createTileMap(width, depth);
    newRoom->sideRooms = NULL;

    return newRoom;
}

void setupMapTest() {
    int width = 4;
    int depth = 4;
    int rangeDepth = (depth * 2 + 1);

    test = (MAP *) malloc(sizeof(MAP));
    test->initialRoom = createRoom(0, width, depth);

    int idx;

    // Snowman (3, -1)
    idx = (3 + width) * rangeDepth + (-1 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scSnowman, 0.0));

    // ConveyorBelt (0, 0)
    idx = (0 + width) * rangeDepth + (0 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scConveyorBelt, 0.0));

    // StartM (0, 0)
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scStartM, 0.0));

    // Funnel (0, 0)
    // insertElement(&(test->initialRoom->tileArray[idx]), createElement(scFunnel, 90.0));

    // Christmas Tree (-3, -3)
    idx = (-3 + width) * rangeDepth + (-3 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scChristmasTree, 0.0));

    // Explicit Walls (Back row z=-4) - Reverse order of drawTestSceneObjects
    
    // Wall (3, -4)
    idx = (3 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWall, 0.0));

    // Door (2, -4)
    idx = (2 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scDoor, 0.0));

    // Wall (1, -4)
    idx = (1 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWall, 0.0));

    // Window (0, -4)
    idx = (0 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWindow, 0.0));

    // Window (-1, -4)
    idx = (-1 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWindow, 0.0));

    // Wall (-2, -4)
    idx = (-2 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWall, 0.0));

    // Wall (-3, -4)
    idx = (-3 + width) * rangeDepth + (-4 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWall, 0.0));

    // Table (-2, 2)
    idx = (-2 + width) * rangeDepth + (2 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scTable, 0.0));

    // Chair (-2, 1)
    idx = (-2 + width) * rangeDepth + (1 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scChair, 0.0));

    // Lamp (-2, 2)
    idx = (-2 + width) * rangeDepth + (2 + depth);
    insertElement(&(test->initialRoom->tileArray[idx]), createElement(scLamp, 0.0));

    // Loop Walls (z = -4)
    for (int x = -3; x <= 3; x++) {
        idx = (x + width) * rangeDepth + (-4 + depth);
        insertElement(&(test->initialRoom->tileArray[idx]), createElement(scWall, 0.0));
    }
}

void setupMapFactory() {
    int width = 4;
    int depth = 4;
    int rangeDepth = (depth * 2 + 1); // recalculate considering negative coords

    factory = (MAP *) malloc(sizeof(MAP));
    factory->initialRoom = createRoom(0, width, depth);
    
    int posX = 2, posZ = 4;
    int index = (posX + width) * rangeDepth + (posZ + depth);

    ELEMENT *newEl = createElement(scChair, 0.0);

    insertElement(&(factory->initialRoom->tileArray[index]), newEl);
}

