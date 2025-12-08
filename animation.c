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

float viewWidthMain = 5.0f;
float viewWidthSecondary = 25.0f;
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
ROOM *nextRoom = NULL;
int isAsking = 1;

int screenChanging = 0;;
float upElevation = 0.0;

void displayMain();
void displaySecondary();
void animation();
void initGL();
void setupSceneLighting();
void drawRoom(ROOM *room);
void drawTreeRecursive(ROOM *room, float x, float z, float xGap, float zGap);
void drawMultipleRooms(ROOM *root, float xSpace, float zSpace);
void setupTextures();
void drawCurrentRoomBorder(ROOM *room);
void keyboard(unsigned char key, int x, int y);
void reshapeMain(int w, int h);
void reshapeSecondary(int w, int h);


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);


    /*
    PRIMARY ROOM
    */
    glutInitWindowSize(960, 960); 
    glutInitWindowPosition(0, 0);
    mainWindow = glutCreateWindow("Christmas Factory - Main");

    initGL();
    setupTextures();

    // lightning and lists are initialized globally
    setupSceneLighting();
    scInitLists();

    // map setup for primary window
    setupMapTest();
    setupMapFactory();  

    /*
    SELECT WHICH MAP TO USE
    */
    // FOR TESTING
    // actualMap = test;
    // actualRoom = test->initialRoom;
    // firstRoom = test->initialRoom;

    // FOR MAIN ANIMATION
    actualMap = factory;
    actualRoom = actualMap->initialRoom;
    firstRoom = actualMap->initialRoom;

    // startTime = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(displayMain);
    glutIdleFunc(animation);
    glutReshapeFunc(reshapeMain);
    glutKeyboardFunc(keyboard);

    /*
    SECONDARY ROOM
    */

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(960, 960); 
    glutInitWindowPosition(961, 0);
    secondaryWindow = glutCreateWindow("Christmas Factory - Main");

    // map setup for secondary window
    initGL();
    setupTextures();
    setupSceneLighting();
    scInitLists();

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

void drawCurrentRoomBorder(ROOM *room) {
    if (!room) return;

    glDisable(GL_LIGHTING); 
    glDisable(GL_TEXTURE_2D);
    glLineWidth(3.0f);
    glColor3f(1.0f, 0.0f, 0.0f);

    float w = (float)room->width + 0.5f;
    float d = (float)room->depth + 0.5f;
    float y = 0.0f;

    glLineWidth(10.0f);

    glBegin(GL_LINE_LOOP);
        glVertex3f(-w, y, -d);
        glVertex3f( w, y, -d);
        glVertex3f( w, y,  d);
        glVertex3f(-w, y,  d);
    glEnd();

    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawRoom(ROOM *room) {    
    if (!room) return;
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

// thanks gemini GOD
void drawTreeRecursive(ROOM *room, float x, float z, float xGap, float zGap) {
    room->visited = 1; // Marcar como dibujado

    // 1. DIBUJAR LA SALA ACTUAL
    glPushMatrix();
        glTranslatef(x, 0.0, z);
        
        // Dibujar el contenido de la sala
        drawRoom(room);
        
        if (room == actualRoom) {
            drawCurrentRoomBorder(room);
        }
    glPopMatrix();

    // 2. PREPARAR PARA DIBUJAR HIJOS
    
    // Contar cuántos hijos válidos hay (no visitados)
    CONNECTION *c = room->sideRooms;
    int validChildren = 0;
    while(c) {
        if (!c->contRoom->visited) validChildren++;
        c = c->nextRoom;
    }

    if (validChildren == 0) return;

    // --- CÁLCULO DE POSICIONES (ROTADO 90 GRADOS) ---

    // A. El "Suelo" del siguiente nivel está a la DERECHA (X positivo)
    // Posición X del padre + Ancho del padre + Gap + (un poco extra para llegar al centro del hijo)
    // Usamos (room->width * 2 + 1) para saltar toda la sala actual
    float nextX = x + xGap + (room->width * 2 + 1); 
    
    // B. Calcular dónde empieza el primer hijo (ARRIBA en el eje Z) para centrarlos verticalmente
    // Estimamos que cada hijo ocupa (profundidad_sala + gap)
    // Centramos el grupo en Z relativo al padre
    float startZ = z - (validChildren * (10.0f + zGap)) / 2.0f; 

    float currentZ = startZ;

    c = room->sideRooms;
    while (c) {
        ROOM *child = c->contRoom;
        
        if (!child->visited) { // Es un hijo
            
            // Dibujar línea conectora (Cable / Pasillo)
            glDisable(GL_LIGHTING);
            glDisable(GL_TEXTURE_2D);
            glColor3f(1.0, 1.0, 0.0); // Amarillo
            glLineWidth(2.0);
            glBegin(GL_LINES);
                // Desde el borde DERECHO del padre
                glVertex3f(x + room->width, 1.0, z); 
                // Al borde IZQUIERDO del hijo
                glVertex3f(nextX - child->width, 1.0, currentZ); 
            glEnd();
            glEnable(GL_LIGHTING);
            glColor3f(1.0, 1.0, 1.0);

            // Llamada recursiva (Avanzamos en X, distribuimos en Z)
            drawTreeRecursive(child, nextX, currentZ, xGap, zGap);
            
            // Mover Z para el siguiente hermano (Hacia ABAJO en el mapa)
            // Usamos la profundidad física del hijo + el espacio
            currentZ += (child->depth * 2 + 1) + zGap + 5.0f; 
        }
        c = c->nextRoom;
    }
}

void drawMultipleRooms(ROOM *rootRoom, float xSpace, float zSpace) {
    if (!rootRoom) return;

    if (actualMap && actualMap->initialRoom) {
        resetGraphFlags(actualMap->initialRoom);
    } else {
        resetGraphFlags(rootRoom); 
    }

    ROOM *startNode = (actualMap && actualMap->initialRoom) ? actualMap->initialRoom : rootRoom;
    
    drawTreeRecursive(startNode, 0.0f, 0.0f, xSpace, zSpace);
}

void displayMain() {
    glClearColor(0.678, 0.847, 0.902, 1.0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(camPosition[X], camPosition[Y], camPosition[Z],
              camPointTo[X], camPointTo[Y], camPointTo[Z],
              0.0, 1.0, 0.0);

    glPushMatrix();
        glTranslatef(0.0, upElevation, 0.0);
        // drawMap(test);
        drawRoom(actualRoom);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, upElevation-10.0f, 0.0);
        drawRoom(nextRoom);
    glPopMatrix();

    glutSwapBuffers();
}

void displaySecondary() {
    glClearColor(0.678, 0.847, 0.902, 1.0); 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(camPosition[X], camPosition[Y], camPosition[Z],
              camPointTo[X], camPointTo[Y], camPointTo[Z],
              0.0, 1.0, 0.0);

    glMatrixMode(GL_MODELVIEW);
    
    drawMultipleRooms(firstRoom, 10.0f, 5.0f);

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
    if (nextRoom) {
        if (upElevation > 10.0f) {
            actualRoom = nextRoom;
            nextRoom = NULL;
            upElevation = 0.0f;
        } 
        else {
            upElevation = upElevation + 0.1f;
            printf("elevating: %f\n", upElevation);
        }
    }
    if (mainWindow > 0) {
        glutSetWindow(mainWindow);
        glutPostRedisplay();
    }
    if (secondaryWindow > 0) {
        glutSetWindow(secondaryWindow);
        glutPostRedisplay();
    }
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
        viewWidthMain -= 0.1;
    }

    else if (key == 'x' || key == 'X') {
        viewWidthMain += 0.1;
    }

    // Initial room. Main Menu
    if (isdigit(key) && isAsking) {
        int roomID = key - '0';
        ROOM *newRoom = getRoom(roomID, actualRoom);
        if (newRoom) {
            screenChanging = glutGet(GLUT_ELAPSED_TIME);
            nextRoom = newRoom;
        }

        else {
            printf("Room %d not found (404)\n", roomID);
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
        glOrtho(-viewWidthMain * aR, viewWidthMain * aR, 
                -viewWidthMain, viewWidthMain, 
                -100.0, 1000.0);
    } else {
        glOrtho(-viewWidthMain, viewWidthMain, 
                -viewWidthMain / aR, viewWidthMain / aR, 
                -100.0, 1000.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void reshapeSecondary(int w, int h) {
    if (h == 0) h = 1;
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    float aR = (float)w / (float)h; // aspect ratio
    
    // glOrtho(left, right, bottom, top, near, far)
    if (w >= h) {
        glOrtho(-viewWidthSecondary * aR, viewWidthSecondary * aR, 
                -viewWidthSecondary, viewWidthSecondary, 
                -100.0, 1000.0);
    } else {
        glOrtho(-viewWidthSecondary, viewWidthSecondary, 
                -viewWidthSecondary / aR, viewWidthSecondary / aR, 
                -100.0, 1000.0);
    }
    
    glMatrixMode(GL_MODELVIEW);
}
