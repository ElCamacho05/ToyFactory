#include "scenes.h"
#include "scenario.h"
#include <stdlib.h>

// Stores the scenes on the animation
SCENE_HASH_TABLE *scene = NULL;
SCENE_HASH_TABLE *actualScene = NULL;

// Hash related functions
unsigned int hashFunction(int id, int size) {
    return (unsigned int) (id%size);
}

// ------------------
// Basic Functions
ELEMENT_NODE *createElement(int id, double *position, double ang) {
    ELEMENT_NODE *el =(ELEMENT_NODE*) malloc(sizeof(ELEMENT_NODE));
    if (el == NULL) return NULL;
    
    el->id = id;
    el->position = position;
    el->ang = ang;
    el->nextElement = NULL;
    return el;
};

// ------------------
// For Hash Functions
SCENE_HASH_TABLE* createElementHashTable() {
    SCENE_HASH_TABLE *ht = (SCENE_HASH_TABLE*)calloc(1, MAX_ELEMENTS_IN_SCENE);
    return ht;
}

void insertElementInHash(SCENE_HASH_TABLE *ht, int id, float *position, float ang) {
    if (!ht || id < 0) return;

    unsigned int index = hashFunction(id, MAX_ELEMENTS_IN_SCENE);
    ELEMENT_NODE *new_node = (ELEMENT_NODE*) malloc(sizeof(ELEMENT_NODE));
    if (!new_node) return;

    new_node->id = id;
    new_node->nextElement = ht->elements[index];
    new_node->position = position;
    new_node->ang = ang;

    ht->elements[index] = new_node;
    ht->count++;
}

int searchElementInHash(SCENE_HASH_TABLE *ht, int id) {
    if (!ht) return NULL;

    unsigned int index = hashFunction(id, MAX_ELEMENTS_IN_SCENE);
    ELEMENT_NODE *current = ht->elements[index];

    while (current != NULL) {
        if (current->id == id) {
            return current->id;
        }
        current = current->nextElement;
    }
    return NULL;
}

void freeElementInHash(SCENE_HASH_TABLE *ht) {
    if (!ht) return;
    for (int i = 0; i < MAX_ELEMENTS_IN_SCENE; i++) {
        ELEMENT_NODE *current = ht->elements[i];
        while (current != NULL) {
            ELEMENT_NODE *temp = current;
            current = current->nextElement;
            free(temp);
        }
    }
    free(ht);
}


// text scenes
void BLACK_SCREEN(char *text) {

}

// turing machine
void initSCENE_1() { // Bletchley Park Enigma's Scene
    
}


void initSCENE_2() {

}

void initSCENE_3() {

}

void initSCENE_4() {

}