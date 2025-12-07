#ifndef SCENARIO_H
#define SCENARIO_H

#include <GL/glut.h>
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

void scInitLists();
    void scInitMapTile();
    void scInitConveyorBelt();
    void scInitLamp();
    void scInitChristmasTree();
    void scInitTable();
    void scInitChair();
    void scInitFunnel();
    void scInitStartM();

    void scInitToyCar();
    void scInitRobotConstructorTorso();
    void scInitRobotExplorerTorso();

    void scInitWall();
    void scInitWindow();
    void scInitDoor();
/*
DRAWING
*/
// Functions
void scDrawMapTile(MATERIAL *mat, TEXTURE *texture);
void scDrawConveyorBelt();
void scDrawLamp();
void scDrawChristmasTree();
void scDrawTable();
void scDrawChair();
void scDrawFunnel();
void scDrawStartM();
void scDrawWall();
void scDrawWindow();
void scDrawDoor();


// IDs
extern GLuint scMapTile;
extern GLuint scConveyorBelt;
extern GLuint scLamp;
extern GLuint scToyCar;
extern GLuint scChristmasTree;
extern GLuint scTable;
extern GLuint scChair;
extern GLuint scStartM;
extern GLuint scFunnel;
extern GLuint scWall;
extern GLuint scWindow;
extern GLuint scDoor;

extern int time;

#endif