// Ejecucion:
// gcc animation.c ScenarioObjects/scenario.c DrawUtils/utils.c DrawUtils/Materials/materials.c DrawUtils/Textures/textures.c -o exec -lGL -lGLU -lglut -lm; ./exec

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#include "ScenarioObjects/scenario.h"
#include "DrawUtils/utils.h"
#include "DrawUtils/Materials/materials.h"
#include "DrawUtils/Textures/textures.h"

#define X 0
#define Y 1
#define Z 2

#define PI 3.14159265359
#define DEG2RAD(x) ((x) * PI / 180.0f)


float camPosition[]= {1.0f, 1.0f, 1.0f};
float camPointTo[]= {0.0f, 0.0f, 0.0f};

float viewWidth = 2.5f;
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

void drawSceneObjects();
void display();
void animation();
void initGL();
void setupSceneLighting();
void drawTestSceneObjects();
void drawTileElements();
void setupTextures();
void keyboard(unsigned char key, int x, int y);
void reshape(int w, int h);

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600); 
    glutCreateWindow("Christmas Factory");

    initGL();
    setupTextures();
    setupSceneLighting();
    scInitLists();         

    // startTime = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(display);
    glutIdleFunc(animation);
    glutReshapeFunc(reshape);
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
    wallTexture = loadTexture("DrawUtils/Textures/Files/wall.jpg");
    woodTexture = loadTexture("DrawUtils/Textures/Files/wood.png");
    rubberTexture = loadTexture("DrawUtils/Textures/Files/rubber.jpg");
    beltTexture = loadTexture("DrawUtils/Textures/Files/belt.png");
    // whitePlasticPattern = loadTexture("DrawUtils/Textures/Files/white-plastic-pattern.png");
    blockyGold = loadTexture("DrawUtils/Textures/Files/blocky-gold.png");
}

void drawTestSceneObjects() {
    int x_range = 1;
    int z_range = 1;

    // draw example tile map
    for (int x=-x_range; x <= x_range; x++) {
        for (int z=-z_range; z <= z_range; z++) {
            glPushMatrix();
                glTranslatef(x, 0.0, z);
                scDrawMapTile(&matWhiteWall, woodTexture);

            glPopMatrix();
        }
    }
    scDrawConveyorBelt();
}

void drawTileElements() {

}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.678, 0.847, 0.902, 1.0); 

    glLoadIdentity();

    gluLookAt(camPosition[X], camPosition[Y], camPosition[Z],
              camPointTo[X], camPointTo[Y], camPointTo[Z],
              0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);

    drawTestSceneObjects();

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

    else {
        return;
    }
}

void reshape(int w, int h) {
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    aspectRatio = (float)w / (float)h;
    
    // glOrtho(left, right, bottom, top, near, far)
    if (w >= h) {
        glOrtho(-viewWidth * aspectRatio, viewWidth * aspectRatio, 
                -viewWidth, viewWidth, 
                -100.0, 1000.0);
    } else {
        glOrtho(-viewWidth, viewWidth, 
                -viewWidth / aspectRatio, viewWidth / aspectRatio, 
                -100.0, 1000.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}
