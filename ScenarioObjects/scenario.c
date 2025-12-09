#include <GL/glut.h>
#include "scenario.h"
#include "../DrawUtils/utils.h"
#include "../DrawUtils/Materials/materials.h"
#include "../DrawUtils/Textures/textures.h"

// furniture
GLuint scMapTile = 0;
GLuint scConveyorBelt = 0;
GLuint scLamp = 0;
GLuint scToyCar = 0;
GLuint scChristmasTree = 0;
GLuint scTable = 0;
GLuint scChair = 0;
GLuint scStartM = 0;
GLuint scFunnel = 0;
GLuint scRoboticArm = 0;
// buildings
GLuint scWall = 0;
GLuint scWindow = 0;
GLuint scDoor = 0;
GLuint scDarkDoor = 0;
// characters
GLuint scSnowman = 0;
/*
MAIN CHARACTER: ROBOT
*/
GLuint scTestRobot = 0;
    GLuint scRobotHeadNormal = 0;
    GLuint scRobotTorsoThin = 0;
    GLuint scRobotTorsoThick = 0;
    GLuint scRobotArmThin = 0;
    GLuint scRobotArmThick = 0;
    GLuint scRobotLegSimple = 0;
    GLuint scRobotLegArmored = 0;
    GLuint scRobotBootSimple = 0;
    GLuint scRobotBootThruster = 0;
    GLuint scRobotBackpack = 0;
    GLuint scRobotJetpack = 0;
    GLuint scRobotAccGlasses = 0;
    GLuint scRobotAccMask = 0;
    GLuint scToolLaser = 0;
    GLuint scToolHammer = 0;
    GLuint scToolSword = 0;
    GLuint scToolLightsaber = 0;

int time = 0;

void scInitLists() {
    // furniture
    scInitMapTile();
    scInitConveyorBelt();
    scInitLamp();
    scInitChristmasTree();
    scInitTable();
    scInitChair();
    scInitFunnel();
    scInitStartM();
    scInitRoboticArm();
    // buildings
    scInitWall();
    scInitWindow();
    scInitDoor();
    scInitDarkDoor();
    // characters
    scInitSnowman();
    scInitRobotParts();
    scInitTestRobot();
}


/*
---------
FURNITURE
---------
*/

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

        // brass casing
        applyMaterial(&matWhiteWall);
        glEnable(GL_TEXTURE_2D);
        if (blockyGold) boundTexture(blockyGold);

            // Top Plate
            glPushMatrix();
                glTranslatef(0.0f, 0.95f, 0.0f);
                glScalef(1.0f, 0.1f, 1.0f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // left wall
            glPushMatrix();
                glTranslatef(-0.45f, 0.5f, 0.0f);
                glScalef(0.1f, 0.8f, 1.0f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // right wall
            glPushMatrix();
                glTranslatef(0.45f, 0.5f, 0.0f);
                glScalef(0.1f, 0.8f, 1.0f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // frontal frame
            glPushMatrix();
                glTranslatef(0.0f, 0.85f, 0.45f);
                glScalef(1.0f, 0.1f, 0.1f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

        glDisable(GL_TEXTURE_2D);

        // rubber flaps
        applyMaterial(&matRubber);
        
        for(float x = -0.3f; x <= 0.3f; x += 0.3f) {
            glPushMatrix();
                glTranslatef(x, 0.55f, 0.45f);
                glScalef(0.28f, 0.5f, 0.05f); 
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

        applyMaterial(&matBrick);
        glEnable(GL_TEXTURE_2D); 
        boundTexture(brickTexture);
            glPushMatrix();
                glScalef(3.0, 2.0, 3.0);
                utDrawTexturedCube(1.0);
            glPopMatrix();

            glPushMatrix();
                glScalef(2, 6.0, 2);
                utDrawTexturedCube(1.0);
            glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        applyMaterial(&matRubber);
        glPushMatrix();
            glScalef(1, 6.01, 1);
            utDrawTexturedCube(1.0);
        glPopMatrix();
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

void scInitRoboticArm() {
    scRoboticArm = glGenLists(1);
    glNewList(scRoboticArm, GL_COMPILE);

        // Base
        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glTranslatef(0.0f, 0.1f, 0.0f);
            glScalef(0.8f, 0.2f, 0.8f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        // Rot axis
        applyMaterial(&matPlasticGreen);
        glPushMatrix();
            glTranslatef(0.0f, 0.35f, 0.0f);
            glScalef(0.4f, 0.3f, 0.4f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, 0.4f, 0.0f); 

            // BOTTOM
            glRotatef(45.0f, 1.0f, 0.0f, 0.0f);

            applyMaterial(&matPlasticGreen);
            glPushMatrix();
                glScalef(0.25f, 0.25f, 0.3f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            glTranslatef(0.0f, 0.4f, 0.0f); 
            
            applyMaterial(&matPlasticRed);
            glPushMatrix();
                glScalef(0.15f, 0.8f, 0.15f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // TOP
            glTranslatef(0.0f, 0.4f, 0.0f);
            glRotatef(95.0f, 1.0f, 0.0f, 0.0f); 
            
            applyMaterial(&matPlasticGreen);
            glPushMatrix();
                glScalef(0.2f, 0.2f, 0.25f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            glTranslatef(0.0f, 0.35f, 0.0f);
            
            applyMaterial(&matPlasticRed);
            glPushMatrix();
                glScalef(0.12f, 0.7f, 0.12f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // GRIPPER
            glTranslatef(0.0f, 0.35f, 0.0f);
            glRotatef(40.0f, 1.0f, 0.0f, 0.0f);

            // Wrist
            applyMaterial(&matPlasticGreen);
            glPushMatrix();
                glScalef(0.2f, 0.15f, 0.3f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            // fingers
            applyMaterial(&matMetalGold);
            glPushMatrix();
                glTranslatef(-0.08f, 0.15f, 0.0f);
                glScalef(0.05f, 0.3f, 0.1f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.08f, 0.15f, 0.0f);
                glScalef(0.05f, 0.3f, 0.1f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        glPopMatrix();
    glEndList();
}

void scDrawRoboticArm() {
    glCallList(scRoboticArm);
}

/*
---------
BUILDINGS
---------
*/

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

// DARK DOOR
void scInitDarkDoor() {
    scDarkDoor = glGenLists(1);
    glNewList(scDarkDoor, GL_COMPILE);
        
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
        applyMaterial(&matConcrete);
        glPushMatrix();
            glTranslatef(0.0f, 1.35f, 0.375f);
            glScalef(0.6f, 2.7f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();
}

void scDrawDarkDoor() {
    glCallList(scDoor);
}

/*
----------
CHARACTERS
----------
*/
void scInitSnowman() {
    scSnowman = glGenLists(1);
    glNewList(scSnowman, GL_COMPILE);

        // body
        applyMaterial(&matWhiteWall); 
        
        // base
        glPushMatrix();
            glTranslatef(0.0f, 0.4f, 0.0f);
            glScalef(0.8f, 0.8f, 0.8f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        // chest
        glPushMatrix();
            glTranslatef(0.0f, 1.1f, 0.0f); 
            glScalef(0.6f, 0.6f, 0.6f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        // head
        glPushMatrix();
            glTranslatef(0.0f, 1.6f, 0.0f);
            glScalef(0.4f, 0.4f, 0.4f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        // nose
        applyMaterial(&matCarrot);
        glPushMatrix();
            glTranslatef(0.0f, 1.6f, 0.2f);
            glScalef(0.04f, 0.04f, 0.2f);
            utDrawTexturedCube(1.0f); 
        glPopMatrix();


        applyMaterial(&matRubber);
        // eyes
        // left
        glPushMatrix(); 
            glTranslatef(-0.1f, 1.65f, 0.21f);
            glScalef(0.05f, 0.05f, 0.05f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        // right
        glPushMatrix();
            glTranslatef(0.1f, 1.65f, 0.21f);
            glScalef(0.05f, 0.05f, 0.05f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        // coal buttons
        for(float y = 1.0f; y <= 1.25f; y += 0.12f) {
            glPushMatrix();
                glTranslatef(0.0f, y, 0.31f);
                glScalef(0.05f, 0.05f, 0.05f);
                utDrawTexturedCube(1.0f);
            glPopMatrix();
        }

        // arms
        applyMaterial(&matBrickBrown);
        // left
        glPushMatrix();
            glTranslatef(-0.35f, 1.2f, 0.0f);
            glRotatef(45, 0, 0, 1);
            glScalef(0.4f, 0.04f, 0.04f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        // right
        glPushMatrix();
            glTranslatef(0.35f, 1.2f, 0.0f);
            glRotatef(-45, 0, 0, 1);
            glScalef(0.4f, 0.04f, 0.04f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();
}

void scDrawSnowman() {
    glCallList(scSnowman);
}


/*
ROBOT
*/
void scInitRobotParts() {
    // -- HEADS --
    scRobotHeadNormal = glGenLists(1);
    glNewList(scRobotHeadNormal, GL_COMPILE);
        applyMaterial(&matPlastic);
        glPushMatrix();
            glScalef(0.5f, 0.5f, 0.5f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        applyMaterial(&matPlasticYellow);
        glPushMatrix();
            glTranslatef(-0.15f, 0.05f, 0.25f);
            glutSolidSphere(0.05, 10, 10);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.15f, 0.05f, 0.25f);
            glutSolidSphere(0.05, 10, 10);
        glPopMatrix();
    glEndList();

    // --- CORE ---
    
    // think chest
    scRobotTorsoThin = glGenLists(1);
    glNewList(scRobotTorsoThin, GL_COMPILE);
        applyMaterial(&matPlasticBlue);
        glPushMatrix();
            glScalef(0.4f, 0.6f, 0.3f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // thick chest
    scRobotTorsoThick = glGenLists(1);
    glNewList(scRobotTorsoThick, GL_COMPILE);
        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glScalef(0.7f, 0.6f, 0.5f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        applyMaterial(&matMetalSilver);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.26f);
            glScalef(0.4f, 0.3f, 0.05f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // -- ARMS --
    // thin arm
    scRobotArmThin = glGenLists(1);
    glNewList(scRobotArmThin, GL_COMPILE);
        applyMaterial(&matPlastic);
        glPushMatrix();
            glTranslatef(0.0f, -0.3f, 0.0f);
            glScalef(0.15f, 0.6f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // thick arm
    scRobotArmThick = glGenLists(1);
    glNewList(scRobotArmThick, GL_COMPILE);

    applyMaterial(&matMetal);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.0f); 
            glScalef(0.35f, 0.35f, 0.35f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glTranslatef(0.0f, -0.4f, 0.0f);
            glScalef(0.25f, 0.5f, 0.25f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // --- LEGS ---
    // simple leg
    scRobotLegSimple = glGenLists(1);
    glNewList(scRobotLegSimple, GL_COMPILE);
        applyMaterial(&matPlastic);
        glPushMatrix();
            glTranslatef(0.0f, -0.3f, 0.0f);
            glScalef(0.2f, 0.6f, 0.2f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // super Leg
    scRobotLegArmored = glGenLists(1);
    glNewList(scRobotLegArmored, GL_COMPILE);
        applyMaterial(&matPlasticBlue);

        glPushMatrix();
            glTranslatef(0.0f, -0.3f, 0.0f);
            glScalef(0.25f, 0.6f, 0.3f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        
        applyMaterial(&matMetalSilver);
        glPushMatrix();
            glTranslatef(0.0f, -0.3f, 0.16f);
            glScalef(0.26f, 0.15f, 0.05f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // -- BOOTS --
    // simple boots
    scRobotBootSimple = glGenLists(1);
    glNewList(scRobotBootSimple, GL_COMPILE);
        applyMaterial(&matRubber);
        glPushMatrix();
            glTranslatef(0.0f, -0.1f, 0.05f);
            glScalef(0.22f, 0.2f, 0.3f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // Propulsion boots
    scRobotBootThruster = glGenLists(1);
    glNewList(scRobotBootThruster, GL_COMPILE);
        applyMaterial(&matMetal);

        glPushMatrix();
            glTranslatef(0.0f, -0.15f, 0.0f);
            glScalef(0.35f, 0.3f, 0.35f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();       
        
        applyMaterial(&matPlasticYellow);
        glPushMatrix();
            glTranslatef(0.0f, -0.35f, 0.0f);
            glScalef(0.15f, 0.1f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // -- BACK ACCESSORIES --
    
    // backpack
    scRobotBackpack = glGenLists(1);
    glNewList(scRobotBackpack, GL_COMPILE);
        applyMaterial(&matBrickBrown);

        glPushMatrix();
            glScalef(0.4f, 0.5f, 0.2f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0f, -0.1f, 0.12f);
            glScalef(0.3f, 0.2f, 0.1f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // Jetpack
    scRobotJetpack = glGenLists(1);
    glNewList(scRobotJetpack, GL_COMPILE);
        applyMaterial(&matMetalSilver);

        glPushMatrix();
            glTranslatef(-0.15f, 0.0f, 0.0f);
            glScalef(0.15f, 0.6f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.15f, 0.0f, 0.0f);
            glScalef(0.15f, 0.6f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();

        applyMaterial(&matDarkMetal);
        glPushMatrix();
            glScalef(0.4f, 0.1f, 0.1f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // -- HEAD ACCESSORIES --

    // Visor/glasses
    scRobotAccGlasses = glGenLists(1);
    glNewList(scRobotAccGlasses, GL_COMPILE);
        applyMaterial(&matPlasticRed);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.0f);
            glScalef(0.52f, 0.1f, 0.05f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // Mask
    scRobotAccMask = glGenLists(1);
    glNewList(scRobotAccMask, GL_COMPILE);
        applyMaterial(&matDarkMetal);
        glPushMatrix();
            glTranslatef(0.0f, -0.15f, 0.26f);
            glScalef(0.4f, 0.2f, 0.05f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0f, -0.15f, 0.3f);
            glScalef(0.1f, 0.1f, 0.1f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // --- TOOLS ---

    // Laser gun
    scToolLaser = glGenLists(1);
    glNewList(scToolLaser, GL_COMPILE);
        applyMaterial(&matPlasticBlue);
        glPushMatrix();
            glTranslatef(0.0f, -0.05f, 0.0f);
            glScalef(0.1f, 0.05f, 0.1f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.0f, 0.1f, 0.2f);
            glScalef(0.12f, 0.12f, 0.5f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // Hammer
    scToolHammer = glGenLists(1);
    glNewList(scToolHammer, GL_COMPILE);
        applyMaterial(&matBrickBrown);
        glPushMatrix();
            glTranslatef(0.0f, 0.2f, 0.0f);
            glScalef(0.08f, 0.6f, 0.08f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        applyMaterial(&matMetal);
        glPushMatrix();
            glTranslatef(0.0f, 0.5f, 0.0f);
            glScalef(0.3f, 0.2f, 0.15f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // Sword
    scToolSword = glGenLists(1);
    glNewList(scToolSword, GL_COMPILE);
        applyMaterial(&matDarkMetal);
        glPushMatrix();
            glTranslatef(0.0f, 0.1f, 0.0f);
            glScalef(0.08f, 0.2f, 0.08f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        applyMaterial(&matMetalGold);
        glPushMatrix();
            glTranslatef(0.0f, 0.25f, 0.0f);
            glScalef(0.3f, 0.05f, 0.1f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
        applyMaterial(&matMetalSilver);
        glPushMatrix();
            glTranslatef(0.0f, 0.6f, 0.0f);
            glScalef(0.06f, 0.7f, 0.02f);
            utDrawTexturedCube(1.0f);
        glPopMatrix();
    glEndList();

    // Lightsaber
    scToolLightsaber = glGenLists(1);
    glNewList(scToolLightsaber, GL_COMPILE);
        applyMaterial(&matMetal);
        glPushMatrix();
            glTranslatef(0.0f, 0.0f, 0.0f);
            glRotatef(-90, 1,0,0);
            utDrawCylinder(0.05f, 0.25f, 8, &matMetal);
        glPopMatrix();
        glDisable(GL_LIGHTING);
        glColor3f(0.0f, 1.0f, 0.0f);
        glPushMatrix();
            glTranslatef(0.0f, 0.25f, 0.0f);
            glRotatef(-90, 1,0,0);
            gluCylinder(gluNewQuadric(), 0.04, 0.04, 0.8, 8, 1);
        glPopMatrix();
        glEnable(GL_LIGHTING);
    glEndList();
}

void scInitTestRobot() {
    scTestRobot = glGenLists(1);
    glNewList(scTestRobot, GL_COMPILE);

    // Core
    glPushMatrix();
        glTranslatef(0.0f, 0.9f, 0.0f); 

        glCallList(scRobotTorsoThin);
        // head
        glPushMatrix();
            glTranslatef(0.0f, 0.55f, 0.0f);
            glCallList(scRobotHeadNormal);
            // glasses
            glCallList(scRobotAccGlasses);
        glPopMatrix();

        // backpack
        glPushMatrix();
            glTranslatef(0.0f, 0.1f, -0.15f);
            glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
            glCallList(scRobotJetpack); 
        glPopMatrix();

        // arms
        // left
        glPushMatrix();
            glTranslatef(-0.28f, 0.25f, 0.0f);
            glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
            glCallList(scRobotArmThin);
            // tool
            glPushMatrix();
                glTranslatef(0.0f, -0.6f, 0.0f);
                glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
                glCallList(scToolLaser);
            glPopMatrix();
        glPopMatrix();

        // Right
        glPushMatrix();
            glTranslatef(0.28f, 0.25f, 0.0f);
            glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
            glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
            glCallList(scRobotArmThin);
             glPushMatrix();
                glTranslatef(0.0f, -0.6f, 0.0f);
                glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
                glCallList(scToolSword);
            glPopMatrix();
        glPopMatrix();

        // legs
        // left
        glPushMatrix();
            glTranslatef(-0.15f, -0.3f, 0.0f);
            glCallList(scRobotLegSimple);
            // boots
            glPushMatrix();
                glTranslatef(0.0f, -0.6f, 0.0f);
                glCallList(scRobotBootThruster);
            glPopMatrix();
        glPopMatrix();
        // right
        glPushMatrix();
            glTranslatef(0.15f, -0.3f, 0.0f);
            glCallList(scRobotLegSimple);
            // boots
            glPushMatrix();
                glTranslatef(0.0f, -0.6f, 0.0f);
                glCallList(scRobotBootThruster);
            glPopMatrix();
        glPopMatrix();

    glPopMatrix();
    glEndList();
}

void scDrawTestRobot() {
    glCallList(scTestRobot);
}

R_CORE *scCreateRobotInstance() {
    R_CORE *robot = (R_CORE*) malloc(sizeof(R_CORE));
    if (!robot) return NULL;

    robot->drawID = scRobotTorsoThin;
    robot->head = NULL;
    robot->arms = NULL;
    robot->legs = NULL;
    robot->back = NULL;
    
    robot->taskQueue = NULL;
    robot->taskQueueLast = NULL;
    
    robot->currentX = 0.0f;
    robot->currentZ = 0.0f;
    robot->isMoving = 0;

    return robot;
}

void scAddRobotTask(R_CORE *robot, float targetX, float targetZ) {
    if (!robot) return;

    R_TASK *newTask = (R_TASK*) malloc(sizeof(R_TASK));
    newTask->x = targetX;
    newTask->z = targetZ;
    newTask->next = NULL;

    if (robot->taskQueue == NULL) {
        robot->taskQueue = newTask;
        robot->taskQueueLast = newTask;
    } else {
        robot->taskQueueLast->next = newTask;
        robot->taskQueueLast = newTask;
    }
    printf("Tarea agregada al robot: Ir a (%.1f, %.1f)\n", targetX, targetZ);
}

R_TASK *scPopRobotTask(R_CORE *robot) {
    if (!robot || !robot->taskQueue) return NULL;

    R_TASK *task = robot->taskQueue;
    robot->taskQueue = task->next;
    
    if (robot->taskQueue == NULL) {
        robot->taskQueueLast = NULL;
    }

    return task;
}