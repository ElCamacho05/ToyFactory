#ifndef SCENARIO_H
#define SCENARIO_H

#include <GL/glut.h>
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

void scInitLists();
    // furniture
    void scInitMapTile();
    void scInitConveyorBelt();
    void scInitLamp();
    void scInitChristmasTree();
    void scInitTable();
    void scInitChair();
    void scInitFunnel();
    void scInitStartM();
    void scInitRoboticArm();
    
    void scInitToyCar();
    void scInitRobotConstructorTorso();
    void scInitRobotExplorerTorso();
    // buildings
    void scInitWall();
    void scInitWindow();
    void scInitDoor();
    // characters
    void scInitSnowman();
/*
DRAWING
*/
// furniture
void scDrawMapTile(MATERIAL *mat, TEXTURE *texture);
void scDrawConveyorBelt();
void scDrawLamp();
void scDrawChristmasTree();
void scDrawTable();
void scDrawChair();
void scDrawFunnel();
void scDrawStartM();
void scDrawRoboticArm();
// buildings
void scDrawWall();
void scDrawWindow();
void scDrawDoor();
// characters
void scDrawSnowman();


// furniture
extern GLuint scMapTile;
extern GLuint scConveyorBelt;
extern GLuint scLamp;
extern GLuint scToyCar;
extern GLuint scChristmasTree;
extern GLuint scTable;
extern GLuint scChair;
extern GLuint scStartM;
extern GLuint scFunnel;
extern GLuint scRoboticArm;
// buildings
extern GLuint scWall;
extern GLuint scWindow;
extern GLuint scDoor;
// characters
extern GLuint scSnowman;


extern int time;

#endif