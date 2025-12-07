#ifndef SCENARIO_H
#define SCENARIO_H

#include <GL/glut.h>
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

void scInitLists();
    void scInitMapTile();
    void scInitConveyorBelt();
    void scInitLamp();
    void scInitToyCar();
    void scInitRobotConstructorTorso();
    void scInitRobotExplorerTorso();

/*
DRAWING
*/
// Functions
void scDrawMapTile(MATERIAL *mat, TEXTURE *texture);
void scDrawConveyorBelt();
void scDrawLamp();

// IDs
extern GLuint scMapTile;
extern GLuint scConveyorBelt;
extern GLuint scLamp;
extern GLuint scToyCar;


extern int time;

#endif