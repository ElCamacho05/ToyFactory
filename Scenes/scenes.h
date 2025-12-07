#ifndef SCENES_H
#define SCENES_H


#define MAX_ELEMENTS_IN_SCENE 100

// Hash table for scene items register
typedef struct ElementNode {
    int id;
    double *position;
    double ang;
    struct ElementNode *nextElement;
} ELEMENT_NODE;

typedef struct SceneHashTable {
    ELEMENT_NODE *elements[MAX_ELEMENTS_IN_SCENE];
    int count;
    int scene_id;
    long duration; // in milliseconds

    float camX;
    float camY;
    float camZ;

    float camYaw; 
    float camPitch;  

    struct SceneHashTable *nextScene; // list of scenes (Hash tables)
} SCENE_HASH_TABLE;

unsigned int hashFunction(int id, int size);
ELEMENT_NODE *createElement(int id, double *position, double ang);
SCENE_HASH_TABLE* createElementHashTable();
void insertElementInHash(SCENE_HASH_TABLE *ht, int id, float *position, float ang);
int searchElementInHash(SCENE_HASH_TABLE *ht, int person_id);
void freeElementInHash(SCENE_HASH_TABLE *ht);

#endif
