#include <GL/glut.h>
#include "scenario.h"
#include "../DrawUtils/utils.h"
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

GLuint scMapTile = 0;
GLuint scConveyorBelt = 0;
GLuint scLamp = 0;
GLuint scToyCar = 0;
GLuint scChristmasTree = 0;
GLuint scTable = 0;
GLuint scChair = 0;
GLuint scStartM = 0;
GLuint scFunnel = 0;
GLuint scWall = 0;
GLuint scWindow = 0;
GLuint scDoor = 0;

int time = 0;

void scInitLists() {
    scInitMapTile();
    scInitConveyorBelt();
    scInitLamp();
    scInitChristmasTree();
    scInitTable();
    scInitChair();
    scInitFunnel();
    scInitStartM();

    scInitWall();
    scInitWindow();
    scInitDoor();
}

// MAP TILES
void scInitMapTile() {
    scMapTile = glGenLists(1);
    glNewList(scMapTile, GL_COMPILE);        
        glPushMatrix();
            glTranslatef(0.0f, -0.1f, 0.0f); 
            glScalef(1.0f, 0.2f, 1.0f); 
            utDrawTexturedCube(1.0);
        glPopMatrix();
    glEndList();
}

void scDrawMapTile(MATERIAL *mat, TEXTURE *texture) {
    if (mat) applyMaterial(mat);
    
    if (texture) {
        glEnable(GL_TEXTURE_2D);
        boundTexture(texture);
    }

    glCallList(scMapTile);
    
    if (texture) {
        glDisable(GL_TEXTURE_2D);
    }
}

// CONVEYOR BELT
void scInitConveyorBelt() {
    scConveyorBelt = glGenLists(1);
    glNewList(scConveyorBelt, GL_COMPILE);

        // Chasis
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(blockyGold);
            glPushMatrix();
                glTranslatef(0.0f, 0.15f, -0.40f);
                glScalef(1.0f, 0.3f, 0.1f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.0f, 0.15f, 0.40f); 
                glScalef(1.0f, 0.3f, 0.1f);       
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        // Rollers
        applyMaterial(&matMetalSilver);
        
        glPushMatrix();
            glTranslatef(-0.4f, 0.15f, -0.4f); 
            utDrawCylinder(0.12f, 0.8f, 8, &matMetalSilver);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.4f, 0.15f, -0.4f); 
            utDrawCylinder(0.12f, 0.8f, 8, &matMetalSilver);
        glPopMatrix();


        // Belt
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(beltTexture);
            // Top-side
            glPushMatrix();
                glTranslatef(0.0f, 0.27f, 0.0f);
                glScalef(0.9f, 0.02f, 0.78f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
            // Bottom-side
            glPushMatrix();
                glTranslatef(0.0f, 0.03f, 0.0f);
                glScalef(0.9f, 0.02f, 0.78f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

    glEndList();
}

void scDrawConveyorBelt() {
    glCallList(scConveyorBelt);
}

// LAMP
void scInitLamp() {
    scLamp = glGenLists(1);
    glNewList(scLamp, GL_COMPILE);
        
        // Base
        applyMaterial(&matDarkMetal);
        glPushMatrix();
            glTranslatef(0.0f, 0.05f, 0.0f);
            glScalef(0.6f, 0.1f, 0.6f);
            glutSolidCube(1.0);
        glPopMatrix();
        
        // Arm
        glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            glScalef(0.1f, 1.0f, 0.1f);
            glutSolidCube(1.0);
        glPopMatrix();

        // REctangular screen
        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glTranslatef(0.0f, 0.8f, 0.0f);
            glScalef(0.5f, 0.4f, 0.5f);
            glutSolidCube(1.0);
        glPopMatrix();

        // light
        GLfloat lightColor[] = {1.0f, 1.0f, 0.9f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, lightColor);
        glPushMatrix();
            glTranslatef(0.0f, 0.8f, 0.0f);
            glScalef(0.51f, 0.1f, 0.51f);
            glutSolidCube(1.0);
        glPopMatrix();
        
        GLfloat noEmit[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, noEmit);

    glEndList();
}

void scDrawLamp() {
    glCallList(scLamp);
}

// CHRISTMAS TREE
void scInitChristmasTree() {
    scChristmasTree = glGenLists(1);
    glNewList(scChristmasTree, GL_COMPILE);
        
        // Wood log
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(darkWoodTexture);
            glPushMatrix();
                glTranslatef(0.0f, 0.4f, 0.0f); 
                glScalef(0.35f, 0.8f, 0.35f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        // Leaves
        applyMaterial(&matPlasticChristmasGreen);
        
        // 1
        glPushMatrix();
            glTranslatef(0.0f, 0.6f, 0.0f);
            glRotatef(-90, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            glutSolidCone(0.65, 1.2, 4, 1);
        glPopMatrix();
        // 2
        glPushMatrix();
            glTranslatef(0.0f, 1.4f, 0.0f);
            glRotatef(-90, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            glutSolidCone(0.5, 1.0, 4, 1);
        glPopMatrix();
        // 3
        glPushMatrix();
            glTranslatef(0.0f, 2.1f, 0.0f);
            glRotatef(-90, 1, 0, 0);
            glRotatef(45, 0, 0, 1);
            glutSolidCone(0.3, 0.9, 4, 1);
        glPopMatrix();

        // Star
        GLfloat lightColor[] = {1.0f, 1.0f, 0.2f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, lightColor);
        
        glPushMatrix();
            glTranslatef(0.0f, 3.05f, 0.0f);
            glutSolidSphere(0.1, 8, 8);
        glPopMatrix();

        GLfloat noEmit[] = {0.0f, 0.0f, 0.0f, 1.0f};
        glMaterialfv(GL_FRONT, GL_EMISSION, noEmit);
    glEndList();
}

void scDrawChristmasTree() {
    glCallList(scChristmasTree);
}

// WOODEN TABLE
void scInitTable() {
    scTable = glGenLists(1);
    glNewList(scTable, GL_COMPILE);
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(darkPlanksTexture);
            // Table
            glPushMatrix();
                glTranslatef(0.0f, 0.85f, 0.0f);
                glScalef(0.9f, 0.1f, 0.9f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            //Legs
            float legPos = 0.35f;
            for(float x = -legPos; x <= legPos; x += legPos*2) {
                for(float z = -legPos; z <= legPos; z += legPos*2) {
                    glPushMatrix();
                        glTranslatef(x, 0.4f, z);
                        glScalef(0.1f, 0.8f, 0.1f);
                        utDrawTexturedCube(1.0f);
                    glPopMatrix();
                }
            }
        glDisable(GL_TEXTURE_2D);
    glEndList();
}

void scDrawTable() {
    glCallList(scTable);
}

// WOODEN CHAIR 
void scInitChair() {
    scChair = glGenLists(1);
    glNewList(scChair, GL_COMPILE);
        
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(darkPlanksTexture);

            // Seat
            glPushMatrix();
                glTranslatef(0.0f, 0.45f, 0.0f);
                glScalef(0.7f, 0.1f, 0.7f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // Legs
            float legPos = 0.25f;
            for(float x = -legPos; x <= legPos; x += legPos*2) {
                for(float z = -legPos; z <= legPos; z += legPos*2) {
                    glPushMatrix();
                        glTranslatef(x, 0.2f, z); 
                        glScalef(0.1f, 0.4f, 0.1f);
                        utDrawTexturedCube(1.0f);
                    glPopMatrix();
                }
            }

            // Back
            glPushMatrix();
                glTranslatef(0.0f, 0.80f, -0.3f);
                glScalef(0.7f, 0.6f, 0.1f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
            
        glDisable(GL_TEXTURE_2D);

        // cushion
        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glTranslatef(0.0f, 0.51f, 0.0f);
            glScalef(0.6f, 0.05f, 0.6f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

    glEndList();
}

void scDrawChair() {
    glCallList(scChair);
}

// FUNNEL
void scInitFunnel() {
    scFunnel = glGenLists(1);
    glNewList(scFunnel, GL_COMPILE);

        // --- 1. CARCASA DE LATÓN (Brass Casing) ---
        // Usamos la textura dorada para el cuerpo principal
        applyMaterial(&matWhiteWall); // Base blanca para que resalte la textura
        glEnable(GL_TEXTURE_2D);
        if (blockyGold) boundTexture(blockyGold);

            // Techo (Top Plate)
            glPushMatrix();
                glTranslatef(0.0f, 0.95f, 0.0f); // Parte más alta
                glScalef(1.0f, 0.1f, 1.0f);      // Placa plana que cubre todo el tile
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // Pared Izquierda
            glPushMatrix();
                glTranslatef(-0.45f, 0.5f, 0.0f); // Borde izquierdo
                glScalef(0.1f, 0.8f, 1.0f);       // Pared alta y profunda
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // Pared Derecha
            glPushMatrix();
                glTranslatef(0.45f, 0.5f, 0.0f);  // Borde derecho
                glScalef(0.1f, 0.8f, 1.0f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // Marco Frontal Superior (El borde de donde cuelgan las gomas)
            glPushMatrix();
                glTranslatef(0.0f, 0.85f, 0.45f); // Frente Arriba
                glScalef(1.0f, 0.1f, 0.1f);       // Barra transversal
                utDrawTexturedCube(1.0f);
            glPopMatrix();

        glDisable(GL_TEXTURE_2D); // Apagamos textura dorada

        // --- 2. CORTINAS DE GOMA (Rubber Flaps) ---
        // Tiras oscuras que cuelgan en la entrada
        applyMaterial(&matRubber); // Material negro mate (definido en materials.c)
        
        // Dibujamos 3 tiras una al lado de la otra
        for(float x = -0.3f; x <= 0.3f; x += 0.3f) {
            glPushMatrix();
                // Posición: Colgando del marco frontal (Y=0.85 hacia abajo)
                // Z=0.45 para estar en la "boca" del túnel
                glTranslatef(x, 0.55f, 0.45f); 
                
                // Dimensión: Tiras verticales (0.28 ancho, 0.5 alto)
                glScalef(0.28f, 0.5f, 0.05f); 
                
                // Detalle: Una ligera rotación aleatoria o fija para que parezca que algo pasó
                // glRotatef(15.0f, 1.0f, 0.0f, 0.0f); // Descomenta para darles ángulo
                
                // Usamos el cubo texturizado (aunque sin textura activa) para aprovechar las normales correctas
                utDrawTexturedCube(1.0f); 
            glPopMatrix();
        }

    glEndList();
}

void scDrawFunnel() {
    glCallList(scFunnel);
}

// STARTING MACHINE
void scInitStartM() {
    scStartM = glGenLists(1);
    glNewList(scStartM, GL_COMPILE);
        glPushMatrix();
            glTranslatef(2.0, 0.0, 0.0);
            glCallList(scConveyorBelt);
            glTranslatef(1.0, 0.0, 0.0);
            glCallList(scConveyorBelt);
            glTranslatef(-1.0, 0.0, 0.0);
            glRotatef(90.0, 0.0, 1.0, 0.0);
            glCallList(scFunnel);
            glCallList(scFunnel);
        glPopMatrix();
    
        applyMaterial(&matPlasticRed);
        glBegin(GL_TEXTURE_2D);
        boundTexture(brickTexture);
            glScalef(3.0, 2.0, 3.0);
            utDrawTexturedCube(1.0);
        glEnd();

    glEndList();
}

void scDrawStartM() {
    glCallList(scStartM);
}

void scInitToyCar() {
    scToyCar = glGenLists(1);
    glNewList(scToyCar, GL_COMPILE);
        
        // --- Chasis ---
        applyMaterial(&matPlasticBlue);
        glPushMatrix();
            glTranslatef(0.0f, 0.3f, 0.0f);
            glScalef(1.0f, 0.4f, 0.6f);
            glutSolidCube(1.0);
        glPopMatrix();

        // --- Cabina ---
        applyMaterial(&matPlasticYellow); // Ventana simulada
        glPushMatrix();
            glTranslatef(0.1f, 0.6f, 0.0f);
            glScalef(0.5f, 0.3f, 0.5f);
            glutSolidCube(1.0);
        glPopMatrix();

        // --- Ruedas (4 Cilindros) ---
        applyMaterial(&matRubber);
        float wheelX[] = {-0.3f, 0.3f};
        float wheelZ[] = {-0.35f, 0.35f}; // Sobresalen un poco del ancho 0.6
        
        for(int i=0; i<2; i++) {
            for(int j=0; j<2; j++) {
                glPushMatrix();
                    glTranslatef(wheelX[i], 0.15f, wheelZ[j]);
                    glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rueda parada
                    // Rueda como cilindro plano
                    glutSolidTorus(0.05, 0.15, 10, 20); 
                glPopMatrix();
            }
        }
    glEndList();
}

void scInitRobotConstructorTorso() {

}

void scInitRobotExplorerTorso() {
    
}

// WALL
void scInitWall() {
    scWall = glGenLists(1);
    glNewList(scWall, GL_COMPILE);
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(darkWoodTexture);
            glPushMatrix();
                glTranslatef(0.0f, 1.5f, 0.375f);
                glScalef(1.0f, 3.0f, 0.25f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();
}

void scDrawWall() {
    glCallList(scWall);
}

// WINDOW
void scInitWindow() {
    scWindow = glGenLists(1);
    glNewList(scWindow, GL_COMPILE);
        // Frame
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        boundTexture(darkWoodTexture);
            // top frame
            glPushMatrix();
                glTranslatef(0.0, 0.5, 0.375);
                glScalef(1.0, 1.0, 0.25);
                utDrawTexturedCube(1.0);
            glPopMatrix();

            // bottom frame
            glPushMatrix();
                glTranslatef(0.0, 2.5, 0.375);
                glScalef(1.0, 1.0, 0.25);
                utDrawTexturedCube(1.0);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        GLfloat glassAmb[] = {0.4, 0.4, 0.9, 0.6}; 
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, glassAmb);
        glEnable(GL_BLEND);
            // FOR ALPHA TRANSPARENCY
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            
            glPushMatrix();
                glTranslatef(0.0f, 1.5f, 0.375);
                glScalef(1.0f, 1.0f, 0.125f);
                glutSolidCube(1.0f);
            glPopMatrix();
            
        glDisable(GL_BLEND);
    glEndList();
}

void scDrawWindow() {
    glCallList(scWindow);
}

// DOOR
void scInitDoor() {
    scDoor = glGenLists(1);
    glNewList(scDoor, GL_COMPILE);
        
        // Frame
        applyMaterial(&matWhiteWall);     
        glEnable(GL_TEXTURE_2D); 
        boundTexture(darkWoodTexture);
            // top 
            glPushMatrix();
                glTranslatef(0.0f, 2.85f, 0.375f); 
                glScalef(1.0f, 0.3f, 0.25f); 
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            
            // left/right
            glPushMatrix();
                glTranslatef(-0.4f, 1.35f, 0.375f);
                glScalef(0.2f, 2.7f, 0.25f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.4f, 1.35f, 0.375f);
                glScalef(0.2f, 2.7f, 0.25f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        // door
        applyMaterial(&matWhiteWall);
        glPushMatrix();
            glTranslatef(0.0f, 1.35f, 0.375f);
            glScalef(0.6f, 2.7f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        // lock
        glEnable(GL_TEXTURE_2D); 
        boundTexture(blockyGold);
        applyMaterial(&matMetalGold);
        glPushMatrix();
            glTranslatef(0.2f, 1.0f, 0.375f);
            glScalef(0.125f, 0.25f, 0.5f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    glEndList();
}
void scDrawDoor() {
    glCallList(scDoor);
}
