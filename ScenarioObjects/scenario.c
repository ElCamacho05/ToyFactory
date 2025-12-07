#include <GL/glut.h>
#include "scenario.h"
#include "../DrawUtils/utils.h"
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

GLuint scMapTile = 0;
GLuint scConveyorBelt = 0;
GLuint scLamp = 0;
GLuint scToyCar = 0;

int time = 0;

void scInitLists() {
    scInitMapTile();
    scInitConveyorBelt();
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


        // Rodillo Delantero (X positivo)
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

void scInitLamp() {
    scLamp = glGenLists(1);
    glNewList(scLamp, GL_COMPILE);
        // Base
        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glScalef(1.0f, 0.2f, 1.0f);
            glutSolidSphere(0.5, 20, 20);
        glPopMatrix();

        // Arm
        applyMaterial(&matMetal);
        glPushMatrix();
            // 1
            glTranslatef(0.0f, 0.1f, 0.0f);
            glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Inclinación hacia atrás
            utDrawCylinder(0.05f, 1.5f, 10, &matMetal);
            
            // .
            glTranslatef(0.0f, 0.0f, 1.5f);
            glutSolidSphere(0.1, 10, 10);
            
            // 2
            glRotatef(75.0f, 1.0f, 0.0f, 0.0f); 
            utDrawCylinder(0.05f, 1.2f, 10, &matMetal);
            
            // Screen
            glTranslatef(0.0f, 0.0f, 1.2f);
            
            // art
            glutSolidSphere(0.1, 10, 10);
            
            glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
            
            // Pantalla Roja
            applyMaterial(&matPlasticRed);
            GLUquadricObj *q = gluNewQuadric();
            gluCylinder(q, 0.1f, 0.6f, 0.8f, 20, 20); 
            gluDeleteQuadric(q);

            // --- Bombilla (Emisiva) ---
            glPushMatrix();
                glTranslatef(0.0f, 0.0f, 0.4f); // Dentro de la pantalla
                // Material brillante/blanco
                GLfloat matEmissive[] = {1.0f, 1.0f, 0.8f, 1.0f};
                glMaterialfv(GL_FRONT, GL_EMISSION, matEmissive); 
                glutSolidSphere(0.2, 15, 15);
                // Apagar emisión para lo siguiente
                GLfloat noEmit[] = {0.0f, 0.0f, 0.0f, 1.0f};
                glMaterialfv(GL_FRONT, GL_EMISSION, noEmit);
            glPopMatrix();

        glPopMatrix();
    glEndList();
}

void scDrawLamp() {
    glCallList(scLamp);
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

