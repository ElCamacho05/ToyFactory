#ifndef UTILS_H
#define UTILS_H

#include <GL/glut.h>

#define LIGHT_ID_UNASSIGNED ((GLenum)-1)

typedef struct light
{
    /*
    
    Estructura para crear luces prefabricadas para el escenario, puedes añadir tantas como quieras en assets.c
    y luego al crear el escenario solo tienes que llamar a la que quieras usar.
    */


    float position[4];          // posición (x,y,z,w). Si w=0 => direccional
    float ambient[4];           // componente ambiental RGBA 
    float diffuse[4];           // componente difuso RGBA
    float specular[4];          // componente especular RGBA
    float intensity;            // multiplicador global de la luz 
    int transmitter;            // 1 = realmente emite (Sol), 0 = no 
    GLenum ID;                   // GL_LIGHTn (para bindear a OpenGL)

}LIGHT;

typedef struct material
{
    /*
    
    Estructura para crear materiales prefabricados, añadelos a assets.c con el formato que ves ahi
    y al crear un planeta solo tienes que llamar tu asset y listo

    */

    float ambient[4];    // componente ambiental RGBA
    float diffuse[4];    // componente difusa RGBA
    float specular[4];   // componente especular RGBA
    float shininess;     // brillo especular (0–128 típico en OpenGL)
} MATERIAL;

LIGHT *createLight(LIGHT *tmplt);
GLenum createID(GLint lid);

// Registra un template de luz en el sistema y devuelve el puntero al template
// actualizado (copia los valores devueltos por la luz creada). Esto permite
// trabajar con las variables globales de tipo LIGHT que el usuario ya tenga.
LIGHT *registerLight(LIGHT *tmplt);

// Funciones para obtener configuraciones de luces predefinidas (Factory)
LIGHT getSunLightConfig();
LIGHT getStreetLampConfig();

// Actualiza la posición almacenada en la estructura LIGHT y la envía a OpenGL
void setLightPosition(LIGHT *l, float x, float y, float z);

// Dibuja una representación visible (esfera emisiva) de la luz en la escena.
// Útil para depuración/visualización. Esta función desactiva temporalmente
// la iluminación para dibujar la esfera con color puro.
void paintLight(LIGHT *l, float x, float y, float z, float radius);

// Aplica un MATERIAL a OpenGL (ambient, diffuse, specular, shininess)
void applyMaterial(MATERIAL *m);

// ELEMENTOS BASICOS (UTILS) DE DIBUJO PARA SCENARIO
// mas basicos
void utDrawTexturedCube(float size);
void utDrawFloor(float width, float depth, MATERIAL *mat);
void utDrawRectangle(double width, double height, MATERIAL *mat);
void utDrawBall(double radius, GLint slices, GLint stacks, MATERIAL *ballMat);
void utDrawCylinder(float radius, float height, int slices, MATERIAL *mat);
// compuestos
void utDrawBrick(double width, double height, double depth, MATERIAL *brickMat);

// TEXTO
void drawText(const char *text, int x, int y, void* font, float r, float g, float b);
void drawDialogueBox(const char *speaker, const char *message);

#define LIGHT_ID_UNASSIGNED ((GLenum)-1)

extern GLint GL_LID;
extern GLint maxL;

extern LIGHT testLight;
extern LIGHT robotLight;

#endif