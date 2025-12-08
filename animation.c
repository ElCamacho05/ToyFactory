// Ejecucion:
// gcc animation.c ScenarioObjects/worldImplementationp.c ScenarioObjects/worldSetup.c ScenarioObjects/scenario.c DrawUtils/utils.c DrawUtils/Materials/materials.c DrawUtils/Textures/textures.c -o exec -lGL -lGLU -lglut -lm; ./exec

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <ctype.h>

#include "ScenarioObjects/scenario.h"
#include "ScenarioObjects/world.h"
#include "DrawUtils/utils.h"
#include "DrawUtils/Materials/materials.h"
#include "DrawUtils/Textures/textures.h"


#define X 0
#define Y 1
#define Z 2

#define PI 3.14159265359
#define DEG2RAD(x) ((x) * PI / 180.0f)

int mainWindow;
int secondaryWindow;

float camPosition[]= {1.0f, 1.0f, 1.0f};
float camPointTo[]= {0.0f, 0.0f, 0.0f};

float viewWidth = 5.0f;
float aspectRatio = 1.0f;

float speed = 0.5f;     
float sensitivity = 2.0f; 

GLenum light = 0;
LIGHT streetLight1;
LIGHT streetLight2;
LIGHT sunLight;

long startTime = 0.0;
float sceneTime = 0.0f;
long beforeSceneTime = 0.0;

MAP *actualMap;;
ROOM *actualRoom;
int isAsking = 0;

void displayMain();
void displaySecondary();
void animation();
void initGL();
void setupSceneLighting();
void drawTestSceneObjects();
void drawRoom(ROOM *room);
void drawMultipleRooms();
void setupTextures();
void keyboard(unsigned char key, int x, int y);
void reshapeMain(int w, int h);
void reshapeSecondary(int w, int h);


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(960, 960); 
    glutInitWindowPosition(0, 0);
    mainWindow = glutCreateWindow("Christmas Factory - Main");

    initGL();
    setupTextures();
    setupSceneLighting();
    scInitLists();

    // map setup
    setupMapTest();
    setupMapFactory();  

    actualMap = factory;

    actualRoom = factory->initialRoom;

    // startTime = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(displayMain);
    glutIdleFunc(animation);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);

    /*
    SECONDARY ROOM
    */

    glutInitWindowSize(960, 960); 
    glutInitWindowPosition(961, 0);
    secondaryWindow = glutCreateWindow("Christmas Factory - Main");

    glutDisplayFunc(displaySecondary);
    glutIdleFunc(animation);
    glutReshapeFunc(reshapeSecondary);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}


void setupSceneLighting() {
    streetLight1 = getStreetLampConfig();
    streetLight1.ID = createID(GL_LID);
    registerLight(&streetLight1);

    streetLight2 = getStreetLampConfig();
    streetLight2.ID = createID(GL_LID);
    registerLight(&streetLight2);
}

void setupTextures() {
    // wood
    darkWoodTexture = loadTexture("DrawUtils/Textures/Files/dark-wood.png");
    // darkWoodTexture = loadTexture("DrawUtils/Textures/Files/dark.png");
    darkPlanksTexture = loadTexture("DrawUtils/Textures/Files/dark-planks.jpg");
    whiteWoodTexture = loadTexture("DrawUtils/Textures/Files/white-wood.jpg");
    whitePlanksTexture = loadTexture("DrawUtils/Textures/Files/white-planks.png");

    // materials
    wallTexture = loadTexture("DrawUtils/Textures/Files/wall.jpg");
    rubberTexture = loadTexture("DrawUtils/Textures/Files/rubber.jpg");
    beltTexture = loadTexture("DrawUtils/Textures/Files/belt.png");
    brickTexture = loadTexture("DrawUtils/Textures/Files/brick.jpg");
    // whitePlasticPattern = loadTexture("DrawUtils/Textures/Files/white-plastic-pattern.png");
    blockyGold = loadTexture("DrawUtils/Textures/Files/blocky-gold.png");
}

void drawTestSceneObjects() {
    int x_range = 3;
    int z_range = 3;

    // draw example tile map
    for (int x=-x_range; x <= x_range; x++) {
        for (int z=-z_range; z <= z_range; z++) {
            glPushMatrix();
                glTranslatef(x, 0.0, z);
                scDrawMapTile(&matWhiteWall, whitePlanksTexture);

            glPopMatrix();
        }
        glPushMatrix();
            glRotatef(90.0, 0.0, 1.0, 0.0);
            glTranslatef(x, 0.0, -4.0);
            glPushMatrix();
            scDrawWall();
        glPopMatrix();
    }

    glPushMatrix();
        glTranslatef(-2.0, 1.0, 2.0);
        scDrawLamp();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.0, 0.0, 1.0);
        scDrawChair();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.0, 0.0, 2.0);
        scDrawTable();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.0, 0.0, -4.0);
        scDrawWall();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-2.0, 0.0, -4.0);
        scDrawWall();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.0, 0.0, -4.0);
        scDrawWindow();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 0.0, -4.0);
        scDrawWindow();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.0, 0.0, -4.0);
        scDrawWall();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(2.0, 0.0, -4.0);
        scDrawDoor();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(3.0, 0.0, -4.0);
        scDrawWall();
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-3.0, 0.0, -3.0);
        scDrawChristmasTree();
    glPopMatrix();

    glPushMatrix();
        // glTranslatef(-1.0, 0.0, -1.0);
        glRotatef(90.0, 0.0, 1.0, 0.0);
        scDrawFunnel();
    glPopMatrix();

    scDrawStartM();
    scDrawConveyorBelt();

    glPushMatrix();
        glTranslatef(3.0, 0.0, -1.0);
        scDrawSnowman();
    glPopMatrix();

}

void drawRoom(ROOM *room) {    
    TILE **tiles = (room->tileArray); 
    
    int roomWidth = room->width * 2 + 1;
    int roomDepth = room->depth * 2 + 1;
    int totalTiles = roomWidth * roomDepth;

    for (int i = 0; i < totalTiles; i++) {
        if (tiles[i] != NULL) { 
            glPushMatrix();
                glTranslatef(tiles[i]->position[0], 0.0, tiles[i]->position[1]);
                scDrawMapTile(&matWhiteWall, whitePlanksTexture);

                // element drawing
                ELEMENT *current = tiles[i]->head;
                
                float height = 0.0;
                while (current != NULL) {
                    glPushMatrix();
                        glTranslatef(0.0, height, 0.0);
                        glRotatef(current->angle, 0.0, 1.0, 0.0);

                        if (current->drawId > 0) { // consider phantom element
                            glCallList(current->drawId);
                        }
                    glPopMatrix();
                    height += 1.0;
                    current = current->next;
                }
            glPopMatrix();
        }
    }
}

void drawMultipleRooms() {
}

void displayMain() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.678, 0.847, 0.902, 1.0); 

    glLoadIdentity();

    gluLookAt(camPosition[X], camPosition[Y], camPosition[Z],
              camPointTo[X], camPointTo[Y], camPointTo[Z],
              0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    
    // drawMap(test);
    drawRoom(actualRoom);

    glutSwapBuffers();
}

void displaySecondary() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.678, 0.847, 0.902, 1.0); 

    glLoadIdentity();

    gluLookAt(camPosition[X], camPosition[Y], camPosition[Z],
              camPointTo[X], camPointTo[Y], camPointTo[Z],
              0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    
    drawMultipleRooms();

    glutSwapBuffers();
}

void animation() {
    long now = glutGet(GLUT_ELAPSED_TIME);
    sceneTime = now - beforeSceneTime;

    // if (sceneTime - actualScene->duration > 0) {
    //     // updating time of simulation
    //     beforeSceneTime += actualScene->duration;
    //     actualScene = actualScene->nextScene;

    //     // updating camera position for simulation
    //     camX = actualScene->camX;
    //     camX = actualScene->camX;
    //     camX = actualScene->camX;
    //     camPitch = actualScene->camPitch;
    //     camYaw = actualScene->camYaw;
    // }

    glutPostRedisplay();
}

void initGL() {
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 0.1, 1000.0); 
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

    else if (key == 'z' || key == 'Z') {
        viewWidth -= 0.1;
    }

    else if (key == 'x' || key == 'X') {
        viewWidth += 0.1;
    }

    // Initial room. Main Menu
    if (isdigit(key) && isAsking) {
        ROOM *newRoom = getRoom(1, actualRoom);
        if (newRoom) actualRoom = newRoom;

        else {
            printf("Room %s not found (404)\n", key);
        }
    }

    else {
        return;
    }
    glutPostRedisplay();
}

void reshapeMain(int w, int h) {
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aR = (float)w / (float)h;
    
    // glOrtho(left, right, bottom, top, near, far)
    if (w >= h) {
        glOrtho(-viewWidth * aR, viewWidth * aR, 
                -viewWidth, viewWidth, 
                -100.0, 1000.0);
    } else {
        glOrtho(-viewWidth, viewWidth, 
                -viewWidth / aR, viewWidth / aR, 
                -100.0, 1000.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void reshapeSecondary(int w, int h) {
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aR = (float)w / (float)h;
    
    // glOrtho(left, right, bottom, top, near, far)
    if (w >= h) {
        glOrtho(-viewWidth * aR, viewWidth * aR, 
                -viewWidth, viewWidth, 
                -100.0, 1000.0);
    } else {
        glOrtho(-viewWidth, viewWidth, 
                -viewWidth / aR, viewWidth / aR, 
                -100.0, 1000.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}
