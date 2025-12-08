#ifndef MATERIALS_H
#define MATERIALS_H

#include "../utils.h"

// Matte/Opaque materials (low specular, low shininess)
extern MATERIAL matBrick;           // red brick
extern MATERIAL matBrickBrown;      // brown brick
extern MATERIAL matBrickGray;       // gray brick
extern MATERIAL matBeigeWall;       // beige wall / plaster
extern MATERIAL matWhiteWall;       // white wall
extern MATERIAL matCeramicFloor;    // ceramic floor
extern MATERIAL matFloorTile;       // dull floor

// Plastic materials (medium specular, medium shininess)
extern MATERIAL matPlastic;         // gray plastic (base)
extern MATERIAL matPlasticRed;      // red plastic
extern MATERIAL matPlasticBlue;     // blue plastic
extern MATERIAL matPlasticGreen;    // green plastic
extern MATERIAL matPlasticYellow;   // yellow plastic

// Metallic materials (high specular, high shininess)
extern MATERIAL matMetal;           // neutral steel
extern MATERIAL matMetalSilver;     // shiny silver
extern MATERIAL matMetalGold;       // gold
extern MATERIAL matMetalCopper;     // copper/bronze
extern MATERIAL matMetalDull;       // dull/brushed metal

extern MATERIAL matPlasticChristmasGreen;
extern MATERIAL matDarkMetal;       // Metal oscuro (Gabinete Turing, Armas)
extern MATERIAL matBakelite;        // Baquelita rojiza (Rotores Enigma, Radios antiguas)
extern MATERIAL matRubber;          // Caucho negro mate (Llantas)
extern MATERIAL matCamoGreen;       // Verde militar mate (Tanques, Aviones)
extern MATERIAL matCamoBrown;       // Marrón tierra mate (Camuflaje)

// Materiales Naturales / Entorno
extern MATERIAL matWater;           // Agua azulada brillante (Río)
extern MATERIAL matAsphalt;         // Asfalto gris oscuro (Carretera)
extern MATERIAL matGrass;           // Hierba verde (Suelo)
extern MATERIAL matConcrete;        // Concreto gris claro (Puente, Búnkers)
extern MATERIAL matCarrot;

// Special materials
extern MATERIAL matGlass;           // glass-like (low diffuse, high specular)
extern MATERIAL matEmissive;        // emissive (for light sources)

#endif // MATERIALS_H