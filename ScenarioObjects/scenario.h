#ifndef SCENARIO_H
#define SCENARIO_H

#include <GL/glut.h>
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

typedef struct RobotCore R_CORE;
    typedef struct RobotHead R_HEAD;
        typedef struct RobotAcc R_F_ACC;
    typedef struct RobotArms R_ARMS;
        typedef struct RobotHands R_HANDS;
            typedef struct RobotTool R_TOOL;
    typedef struct RobotLegs R_LEGS;
        typedef struct RobotBoots R_BOOTS;
    typedef struct RobotBack R_BACK;

typedef struct RobotCore {
    int drawID;
    R_HEAD *head;
    R_ARMS *arms;
    R_LEGS *legs;
    R_BACK *back;
} R_CORE;

    typedef struct RobotHead {
        int drawID;
        R_F_ACC *f_acc;
    } R_HEAD;

        typedef struct RobotAcc {
            int drawID;
        } R_F_ACC;

    typedef struct RobotArms {
        int drawID;
        R_HANDS *hand;
    } R_ARMS;

        typedef struct RobotTool {
            int drawID;
        } R_TOOL;

    typedef struct RobotLegs {
        int drawID;
        R_BOOTS *boots;
    } R_LEGS;

        typedef struct RobotBoots {
            int drawID;
        } R_BOOTS;

    typedef struct RobotBack {
        int drawID;
    } R_BACK;

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