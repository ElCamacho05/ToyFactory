#ifndef WORLD_H
#define WORLD_H

typedef struct element {
    int drawId;
    struct element *next;
} ELEMENT;

typedef struct mapTile{
    int position[2];
    ELEMENT *elementList;
}MAP_TILE;

#endif