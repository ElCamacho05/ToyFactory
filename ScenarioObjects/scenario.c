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
}


void scInitMapTile() {
    scMapTile = glGenLists(1);
    glNewList(scMapTile, GL_COMPILE);
        // Material de suelo industrial limpio
        
        glPushMatrix();
            // Centramos el tile (asumiendo tiles de 2x2 unidades)
            // Grosor de 0.2 para que se vea sólido
            glTranslatef(0.0f, -0.1f, 0.0f); 
            glScalef(1.0f, 0.2f, 1.0f); 
            utDrawTexturedCube(1.0);
            
            // Borde opcional para diferenciar tiles (simulado con un wireframe o color diferente)
            // O simplemente confiamos en la iluminación del cubo
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

void scInitConveyorBelt() {
    scConveyorBelt = glGenLists(1);
    glNewList(scConveyorBelt, GL_COMPILE);
        
        // --- La Base de la cinta (Metal oscuro) ---
        // applyMaterial(&matDarkMetal);
        glPushMatrix();
            glScalef(2.0f, 0.5f, 1.8f); // Un poco más estrecha que el tile completo
            glutSolidCube(1.0);
        glPopMatrix();

        // --- La Banda de Goma (Negra mate) ---
        applyMaterial(&matRubber); 
        glPushMatrix();
            glTranslatef(0.0f, 0.26f, 0.0f); // Apenas encima de la base
            glScalef(2.0f, 0.05f, 1.6f);
            glutSolidCube(1.0);
        glPopMatrix();

        // --- Rodillos (Detalle visual en los extremos) ---
        applyMaterial(&matMetalSilver);
        for(float x = -0.9f; x <= 0.9f; x += 0.6f) {
            glPushMatrix();
                glTranslatef(x, 0.25f, -0.8f); // Lado 'front'
                utDrawCylinder(0.1f, 1.6f, 10, &matMetalSilver); // Rodillo transversal
            glPopMatrix();
        }
    glEndList();
}

void scDrawConveyorBelt() {

}

void scInitLamp() {
    scLamp = glGenLists(1);
    glNewList(scLamp, GL_COMPILE);
        
        // --- Base ---
        applyMaterial(&matPlasticRed); // O matMetalGold para algo clásico
        glPushMatrix();
            glScalef(1.0f, 0.2f, 1.0f);
            glutSolidSphere(0.5, 20, 20); // Base achatada
        glPopMatrix();

        // --- Brazo (Inclinado) ---
        applyMaterial(&matMetal);
        glPushMatrix();
            // Primer segmento
            glTranslatef(0.0f, 0.1f, 0.0f);
            glRotatef(-30.0f, 1.0f, 0.0f, 0.0f); // Inclinación hacia atrás
            utDrawCylinder(0.05f, 1.5f, 10, &matMetal);
            
            // Codo
            glTranslatef(0.0f, 0.0f, 1.5f);
            glutSolidSphere(0.1, 10, 10);
            
            // Segundo segmento (hacia adelante)
            glRotatef(75.0f, 1.0f, 0.0f, 0.0f); 
            utDrawCylinder(0.05f, 1.2f, 10, &matMetal);
            
            // --- Pantalla (Cono cortado) ---
            glTranslatef(0.0f, 0.0f, 1.2f); // Punta del brazo
            
            // Articulación pantalla
            glutSolidSphere(0.1, 10, 10);
            
            glRotatef(45.0f, 1.0f, 0.0f, 0.0f); // Apuntando abajo
            
            // Pantalla Roja
            applyMaterial(&matPlasticRed);
            // GLU Cylinder para cono truncado: base=0.2, top=0.6, height=0.8
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

