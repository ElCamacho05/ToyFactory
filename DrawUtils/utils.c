#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#include "utils.h"
#include "Materials/materials.h"

#define PI 3.14159265359

double tessLevel = 0.25;


GLint maxL = 24;               // Maximo numero de luces soportadas por OpenGL
GLint GL_LID = 0;             // ID de la siguiente luz disponible

LIGHT testLight =  
{
    .position    =  {0,0,0,1},
    .ambient     =  {0.02,0.02,0.02,1},
    .diffuse     =  {1.0,0.95,0.85,1.0},
    .specular    =  {1.0,1.0,1.0,1.0},
    .intensity   =  1.0,
    .transmitter =  1,
    .ID          =  0       // IMPORTANTE QUE AL CREAR TUS LUCES PREFABRICADAS PROPIAS
                                            // LAS MARQUES CON ESTA BANDERA ESPECIAL QUE
                                            // SIMBOLIZA: glID -1 SOLO PARA MARCAR QUE ES UN TEMPLATE  
};

LIGHT *createLight(LIGHT *tmplt)
{
    if(!tmplt) 
        return NULL;

    LIGHT *newL = (LIGHT*)malloc(sizeof(LIGHT));
    if(!newL) 
        return NULL;
    
    *newL = *tmplt;

    // verificar límite y asignar ID si hay espacio 
    if (GL_LID >= maxL)
    {
        newL->ID = LIGHT_ID_UNASSIGNED;
    }
    else
    {
        newL->ID = createID(GL_LID);
        GL_LID++;

        // CREAMOS Y CONECTAMOS LA LUZ
        glEnable(newL->ID);
        glLightfv(newL->ID, GL_AMBIENT, newL->ambient);
        glLightfv(newL->ID, GL_DIFFUSE, newL->diffuse);
        glLightfv(newL->ID, GL_SPECULAR, newL->specular);
        //glLightfv(newL->ID, GL_POSITION, newL->position);
    }
    
    return newL;
}

GLenum createID(GLint lid) {
    return (GLenum)(GL_LIGHT0 + lid);
}

// Registra un template de LIGHT: crea la luz en OpenGL usando createLight(),
// copia los valores devueltos en el template original y libera la estructura
// auxiliar. Devuelve el puntero al template original actualizado o NULL.
LIGHT *registerLight(LIGHT *tmplt)
{
    if (!tmplt) return NULL;
    LIGHT *created = createLight(tmplt);
    if (!created) return NULL;

    // Copiamos los valores esenciales al template del usuario para que pueda
    // seguir usando su variable global 'testLight' directamente.
    tmplt->ID = created->ID;
    for (int i = 0; i < 4; ++i) {
        tmplt->position[i] = created->position[i];
        tmplt->ambient[i]  = created->ambient[i];
        tmplt->diffuse[i]  = created->diffuse[i];
        tmplt->specular[i] = created->specular[i];
    }
    tmplt->intensity = created->intensity;
    tmplt->transmitter = created->transmitter;

    // Ya que OpenGL mantiene el estado, podemos liberar la estructura creada
    free(created);
    return tmplt;
}

void setLightPosition(LIGHT *l, float x, float y, float z)
{
    if (!l) return;
    l->position[0] = x;
    l->position[1] = y;
    l->position[2] = z;
    l->position[3] = 1.0f;
    if (l->ID != LIGHT_ID_UNASSIGNED) {
        glLightfv(l->ID, GL_POSITION, l->position);
    }
}

void paintLight(LIGHT *l, float x, float y, float z, float radius)
{
    if (!l) return;
    // Guardar atributos
    // glPushAttrib(GL_ENABLE_BIT | GL_CURRENT_BIT | GL_LIGHTING_BIT);
    // Queremos dibujar la esfera con color puro (emisión), así que deshabilitamos
    // la iluminación a propósito y pintamos con glColor
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 0.6f);
    glPushMatrix();
        glTranslatef(x, y, z);
        // Usamos GLUT para una esfera simple
        glutSolidSphere(radius, 12, 12);
    glPopMatrix();
    // Restaurar estado
    glEnable(GL_LIGHTING);
    glPopAttrib();
}

void applyMaterial(MATERIAL *m)
{
    if (!m) return;
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m->ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m->diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m->specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, m->shininess);
}

LIGHT getSunLightConfig() {
    LIGHT l = {
        .ambient     = {0.2f, 0.2f, 0.2f, 1.0f},
        .diffuse     = {1.0f, 0.95f, 0.8f, 1.0f}, // Luz cálida
        .specular    = {1.0f, 1.0f, 1.0f, 1.0f},
        .intensity   = 1.0f,
        .transmitter = 1,
        .ID          = -1 // ID temporal
    };
    return l;
}

LIGHT getStreetLampConfig() {
    LIGHT l = {
        .ambient     = {0.0f, 0.0f, 0.0f, 1.0f},
        .diffuse     = {0.8f, 0.8f, 1.0f, 1.0f}, // Luz azulada/fria
        .specular    = {0.5f, 0.5f, 0.5f, 1.0f},
        .intensity   = 0.8f,
        .transmitter = 0.0,
        .ID          = -1
    };
    return l;
}


// FIGURAS SIMPLES
// En utils.c
void utDrawFloor(float width, float depth, MATERIAL *mat) {
    applyMaterial(mat);
    
    // float step = 1.0f; // Tamaño de cada "baldosa" del suelo
    
    // Normal hacia arriba para todo el suelo
    glNormal3f(0.0f, 1.0f, 0.0f);

    glBegin(GL_QUADS);
    for (float x = 0; x < width; x += tessLevel) {
        for (float z = 0; z < depth; z += tessLevel) {
            // Dibuja un cuadrado pequeño
            glVertex3f(x, 0.0f, z);
            glVertex3f(x, 0.0f, z + tessLevel);
            glVertex3f(x + tessLevel, 0.0f, z + tessLevel);
            glVertex3f(x + tessLevel, 0.0f, z);
        }
    }
    glEnd();
}

void utDrawBall(double radius, GLint slices, GLint stacks, MATERIAL *ballMat) {
    // MATERIAL ballMat = {
    //     .ambient   = {0.0f, 0.0f, 0.2f, 1.0f},
    //     .diffuse   = {0.0f, 0.0f, 1.0f, 1.0f}, // Azul
    //     .specular  = {1.0f, 1.0f, 1.0f, 1.0f}, // Brillo blanco fuerte
    //     .shininess = 80.0f
    // };
    
    applyMaterial(ballMat);
    glutSolidSphere(radius, slices, stacks);
}

void utDrawRectangle(double width, double height, MATERIAL *mat) {
    applyMaterial(mat);
        
    glNormal3f(0.0f, 0.0f, 1.0f);

    glBegin(GL_QUADS);
    for (float x = 0; x < width; x += tessLevel) {
        float nextX = (x + tessLevel > width) ? width : x + tessLevel;
        for (float y = 0; y < height; y += tessLevel) {
            float nextY = (y + tessLevel > height) ? height : y + tessLevel;

            glVertex3f(x, y, 0.0f);
            glVertex3f(nextX, y, 0.0f);
            glVertex3f(nextX, nextY, 0.0f);
            glVertex3f(x, nextY, 0.0f);
        }
    }
    glEnd();
}

void utDrawTexturedCube(float size) {
    float s = size / 2.0f;

    // Front
    glNormal3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, -s,  s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s, -s,  s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s,  s,  s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s,  s,  s);
    glEnd();

    // Back
    glNormal3f(0.0f, 0.0f, -1.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, -s, -s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-s,  s, -s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( s,  s, -s);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( s, -s, -s);
    glEnd();

    // top
    glNormal3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s,  s, -s);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s,  s,  s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s,  s,  s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s,  s, -s);
    glEnd();

    // bottom
    glNormal3f(0.0f, -1.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-s, -s, -s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( s, -s, -s);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( s, -s,  s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, -s,  s);
    glEnd();

    // right
    glNormal3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(1.0f, 0.0f); glVertex3f( s, -s, -s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f( s,  s, -s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f( s,  s,  s);
        glTexCoord2f(0.0f, 0.0f); glVertex3f( s, -s,  s);
    glEnd();

    // left
    glNormal3f(-1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-s, -s, -s);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(-s, -s,  s);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(-s,  s,  s);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-s,  s, -s);
    glEnd();
}

void utDrawBrick(double width, double height, double depth, MATERIAL *mat) {
    applyMaterial(mat);
    
    float i, j;
    float nextI, nextJ;

    glBegin(GL_QUADS);

    // --- CARA FRONTAL (Z = 0) ---
    glNormal3f(0.0f, 0.0f, -1.0f); // Apunta hacia afuera (hacia -Z en tu sistema)
    for (i = 0; i < width; i += tessLevel) {
        nextI = (i + tessLevel > width) ? width : i + tessLevel;
        for (j = 0; j < height; j += tessLevel) {
            nextJ = (j + tessLevel > height) ? height : j + tessLevel;
            glVertex3f(i, j, 0.0f);
            glVertex3f(i, nextJ, 0.0f);
            glVertex3f(nextI, nextJ, 0.0f);
            glVertex3f(nextI, j, 0.0f);
        }
    }

    // --- CARA TRASERA (Z = depth) ---
    glNormal3f(0.0f, 0.0f, 1.0f);
    for (i = 0; i < width; i += tessLevel) {
        nextI = (i + tessLevel > width) ? width : i + tessLevel;
        for (j = 0; j < height; j += tessLevel) {
            nextJ = (j + tessLevel > height) ? height : j + tessLevel;
            glVertex3f(nextI, j, depth);
            glVertex3f(nextI, nextJ, depth);
            glVertex3f(i, nextJ, depth);
            glVertex3f(i, j, depth);
        }
    }

    // --- CARA SUPERIOR (Y = height) ---
    glNormal3f(0.0f, 1.0f, 0.0f);
    for (i = 0; i < width; i += tessLevel) {
        nextI = (i + tessLevel > width) ? width : i + tessLevel;
        for (j = 0; j < depth; j += tessLevel) {
            nextJ = (j + tessLevel > depth) ? depth : j + tessLevel;
            glVertex3f(i, height, j);
            glVertex3f(nextI, height, j);
            glVertex3f(nextI, height, nextJ);
            glVertex3f(i, height, nextJ);
        }
    }

    // --- CARA INFERIOR (Y = 0) ---
    glNormal3f(0.0f, -1.0f, 0.0f);
    for (i = 0; i < width; i += tessLevel) {
        nextI = (i + tessLevel > width) ? width : i + tessLevel;
        for (j = 0; j < depth; j += tessLevel) {
            nextJ = (j + tessLevel > depth) ? depth : j + tessLevel;
            glVertex3f(i, 0.0f, nextJ);
            glVertex3f(nextI, 0.0f, nextJ);
            glVertex3f(nextI, 0.0f, j);
            glVertex3f(i, 0.0f, j);
        }
    }

    // --- CARA DERECHA (X = width) ---
    glNormal3f(1.0f, 0.0f, 0.0f);
    for (i = 0; i < depth; i += tessLevel) {
        nextI = (i + tessLevel > depth) ? depth : i + tessLevel;
        for (j = 0; j < height; j += tessLevel) {
            nextJ = (j + tessLevel > height) ? height : j + tessLevel;
            glVertex3f(width, j, i);
            glVertex3f(width, nextJ, i);
            glVertex3f(width, nextJ, nextI);
            glVertex3f(width, j, nextI);
        }
    }

    // --- CARA IZQUIERDA (X = 0) ---
    glNormal3f(-1.0f, 0.0f, 0.0f);
    for (i = 0; i < depth; i += tessLevel) {
        nextI = (i + tessLevel > depth) ? depth : i + tessLevel;
        for (j = 0; j < height; j += tessLevel) {
            nextJ = (j + tessLevel > height) ? height : j + tessLevel;
            glVertex3f(0.0f, j, nextI);
            glVertex3f(0.0f, nextJ, nextI);
            glVertex3f(0.0f, nextJ, i);
            glVertex3f(0.0f, j, i);
        }
    }

    glEnd();
}

void utDrawCylinder(float radius, float height, int slices, MATERIAL *mat) {
    applyMaterial(mat);
    
    float stackHeight = 0.1;

    int stacks = height / stackHeight;

    // --- LATERALES ---
    for (int j = 0; j < stacks; j++) {
        float zLow = j * stackHeight;
        float zHigh = (j + 1) * stackHeight;

        glBegin(GL_TRIANGLE_STRIP);
        for (int i = 0; i <= slices; ++i) {
            float angle = 2.0f * PI * i / slices;
            float x = radius * cos(angle);
            float y = radius * sin(angle);

            glNormal3f(x / radius, y / radius, 0.0f);
            
            // Vértice superior del anillo actual
            glVertex3f(x, y, zHigh); 
            // Vértice inferior del anillo actual
            glVertex3f(x, y, zLow);
        }
        glEnd();
    }
    
    // TOP
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, height);
    for (int i = 0; i <= slices; ++i) {
        float angle = 2.0f * PI * i / slices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, height);
    }
    glEnd();

    // BOTTOM
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, -1.0f);
    glVertex3f(0.0f, 0.0f, 0.0);
    for (int i = slices; i >= 0; --i) {
        float angle = 2.0f * PI * i / slices;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex3f(x, y, 0.0);
    }
    glEnd();
}
