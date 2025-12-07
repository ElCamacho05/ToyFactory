#include "materials.h"

// ============================================================================
// MATTE / OPAQUE MATERIALS (low specular, low shininess)
// ============================================================================

MATERIAL matBrick = {
    .ambient   = {0.3f, 0.05f, 0.03f, 1.0f},
    .diffuse   = {0.8f, 0.2f, 0.15f, 1.0f},
    .specular  = {0.2f, 0.2f, 0.2f, 1.0f},
    .shininess = 8.0f
};

MATERIAL matBrickBrown = {
    .ambient   = {0.35f, 0.15f, 0.05f, 1.0f},
    .diffuse   = {0.7f, 0.4f, 0.15f, 1.0f},
    .specular  = {0.15f, 0.15f, 0.15f, 1.0f},
    .shininess = 6.0f
};

MATERIAL matBrickGray = {
    .ambient   = {0.25f, 0.25f, 0.25f, 1.0f},
    .diffuse   = {0.5f, 0.5f, 0.5f, 1.0f},
    .specular  = {0.1f, 0.1f, 0.1f, 1.0f},
    .shininess = 5.0f
};

MATERIAL matBeigeWall = {
    .ambient   = {0.6f, 0.54f, 0.48f, 1.0f},
    .diffuse   = {0.9f, 0.85f, 0.78f, 1.0f},
    .specular  = {0.05f, 0.05f, 0.05f, 1.0f},
    .shininess = 4.0f
};

MATERIAL matWhiteWall = {
    .ambient   = {0.8f, 0.8f, 0.8f, 1.0f},
    .diffuse   = {0.95f, 0.95f, 0.95f, 1.0f},
    .specular  = {0.08f, 0.08f, 0.08f, 1.0f},
    .shininess = 5.0f
};

MATERIAL matCeramicFloor = {
    .ambient   = {0.3f, 0.3f, 0.3f, 1.0f},
    .diffuse   = {0.6f, 0.6f, 0.6f, 1.0f},
    .specular  = {0.2f, 0.2f, 0.2f, 1.0f},
    .shininess = 12.0f
};

MATERIAL matFloorTile = {
    .ambient   = {0.2f, 0.18f, 0.16f, 1.0f},
    .diffuse   = {0.4f, 0.35f, 0.3f, 1.0f},
    .specular  = {0.1f, 0.1f, 0.1f, 1.0f},
    .shininess = 10.0f
};

// ============================================================================
// PLASTIC MATERIALS (medium specular ~0.6, medium shininess ~20-40)
// ============================================================================

MATERIAL matPlastic = {
    .ambient   = {0.05f, 0.05f, 0.06f, 1.0f},
    .diffuse   = {0.3f, 0.3f, 0.35f, 1.0f},
    .specular  = {0.6f, 0.6f, 0.65f, 1.0f},
    .shininess = 32.0f
};

MATERIAL matPlasticRed = {
    .ambient   = {0.15f, 0.02f, 0.02f, 1.0f},
    .diffuse   = {0.7f, 0.1f, 0.1f, 1.0f},
    .specular  = {0.55f, 0.55f, 0.55f, 1.0f},
    .shininess = 28.0f
};

MATERIAL matPlasticBlue = {
    .ambient   = {0.02f, 0.05f, 0.15f, 1.0f},
    .diffuse   = {0.1f, 0.2f, 0.7f, 1.0f},
    .specular  = {0.55f, 0.55f, 0.6f, 1.0f},
    .shininess = 28.0f
};

MATERIAL matPlasticGreen = {
    .ambient   = {0.02f, 0.15f, 0.02f, 1.0f},
    .diffuse   = {0.1f, 0.7f, 0.1f, 1.0f},
    .specular  = {0.55f, 0.6f, 0.55f, 1.0f},
    .shininess = 28.0f
};

MATERIAL matPlasticYellow = {
    .ambient   = {0.15f, 0.15f, 0.02f, 1.0f},
    .diffuse   = {0.7f, 0.7f, 0.1f, 1.0f},
    .specular  = {0.6f, 0.6f, 0.5f, 1.0f},
    .shininess = 28.0f
};

// ============================================================================
// COMMON METALLIC MATERIALS (high specular ~0.8-0.95, high shininess ~60-100)
// ============================================================================

MATERIAL matMetal = {
    .ambient   = {0.1f, 0.1f, 0.12f, 1.0f},
    .diffuse   = {0.2f, 0.2f, 0.25f, 1.0f},
    .specular  = {0.9f, 0.9f, 0.95f, 1.0f},
    .shininess = 80.0f
};

MATERIAL matMetalSilver = {
    .ambient   = {0.08f, 0.08f, 0.08f, 1.0f},
    .diffuse   = {0.4f, 0.4f, 0.42f, 1.0f},
    .specular  = {0.95f, 0.95f, 0.98f, 1.0f},
    .shininess = 90.0f
};

MATERIAL matMetalGold = {
    .ambient   = {0.3f, 0.25f, 0.05f, 1.0f},
    .diffuse   = {0.75f, 0.6f, 0.2f, 1.0f},
    .specular  = {0.92f, 0.85f, 0.3f, 1.0f},
    .shininess = 85.0f
};

MATERIAL matMetalCopper = {
    .ambient   = {0.25f, 0.1f, 0.05f, 1.0f},
    .diffuse   = {0.8f, 0.3f, 0.1f, 1.0f},
    .specular  = {0.9f, 0.65f, 0.4f, 1.0f},
    .shininess = 75.0f
};

MATERIAL matMetalDull = {
    .ambient   = {0.15f, 0.15f, 0.15f, 1.0f},
    .diffuse   = {0.4f, 0.4f, 0.42f, 1.0f},
    .specular  = {0.5f, 0.5f, 0.52f, 1.0f},
    .shininess = 40.0f
};

// ============================================================================
// INDUSTRIAL & MILITARY MATERIALS
// ============================================================================

MATERIAL matDarkMetal = {
    .ambient   = {0.1f, 0.1f, 0.15f, 1.0f},  // Tono azulado muy oscuro
    .diffuse   = {0.2f, 0.2f, 0.25f, 1.0f},
    .specular  = {0.5f, 0.5f, 0.6f, 1.0f},   // Brillo metálico frío
    .shininess = 30.0f
};

MATERIAL matBakelite = {
    .ambient   = {0.2f, 0.05f, 0.05f, 1.0f}, // Rojizo oscuro
    .diffuse   = {0.4f, 0.1f, 0.1f, 1.0f},
    .specular  = {0.6f, 0.4f, 0.4f, 1.0f},   // Brillo plástico ceroso
    .shininess = 40.0f
};

MATERIAL matRubber = {
    .ambient   = {0.05f, 0.05f, 0.05f, 1.0f}, // Casi negro
    .diffuse   = {0.1f, 0.1f, 0.1f, 1.0f},
    .specular  = {0.02f, 0.02f, 0.02f, 1.0f}, // Sin brillo
    .shininess = 10.0f
};

MATERIAL matCamoGreen = {
    .ambient   = {0.1f, 0.15f, 0.1f, 1.0f},
    .diffuse   = {0.25f, 0.35f, 0.25f, 1.0f}, // Verde oliva apagado
    .specular  = {0.1f, 0.1f, 0.1f, 1.0f},    // Muy poco brillo (mate)
    .shininess = 5.0f
};

MATERIAL matCamoBrown = {
    .ambient   = {0.15f, 0.1f, 0.05f, 1.0f},
    .diffuse   = {0.35f, 0.25f, 0.15f, 1.0f}, // Marrón tierra
    .specular  = {0.1f, 0.1f, 0.1f, 1.0f},
    .shininess = 5.0f
};

// ============================================================================
// ENVIRONMENT MATERIALS
// ============================================================================

MATERIAL matWater = {
    .ambient   = {0.1f, 0.2f, 0.4f, 0.8f},   // Azul profundo
    .diffuse   = {0.2f, 0.4f, 0.7f, 0.8f},
    .specular  = {0.8f, 0.8f, 0.9f, 1.0f},   // Brillo fuerte (reflejo)
    .shininess = 90.0f
};

MATERIAL matAsphalt = {
    .ambient   = {0.15f, 0.15f, 0.15f, 1.0f},
    .diffuse   = {0.25f, 0.25f, 0.25f, 1.0f}, // Gris oscuro rugoso
    .specular  = {0.05f, 0.05f, 0.05f, 1.0f},
    .shininess = 5.0f
};

MATERIAL matGrass = {
    .ambient   = {0.05f, 0.2f, 0.05f, 1.0f},
    .diffuse   = {0.1f, 0.5f, 0.1f, 1.0f},    // Verde vivo
    .specular  = {0.0f, 0.0f, 0.0f, 1.0f},    // La hierba no brilla
    .shininess = 0.0f
};

MATERIAL matConcrete = {
    .ambient   = {0.3f, 0.3f, 0.3f, 1.0f},
    .diffuse   = {0.6f, 0.6f, 0.6f, 1.0f},    // Gris claro
    .specular  = {0.1f, 0.1f, 0.1f, 1.0f},
    .shininess = 10.0f
};

// ============================================================================
// SPECIAL MATERIALS
// ============================================================================

MATERIAL matGlass = {
    .ambient   = {0.02f, 0.03f, 0.04f, 0.25f},
    .diffuse   = {0.2f, 0.25f, 0.3f, 0.25f},
    .specular  = {0.9f, 0.9f, 0.95f, 0.25f},
    .shininess = 100.0f
};

MATERIAL matEmissive = {
    .ambient   = {0.0f, 0.0f, 0.0f, 1.0f},
    .diffuse   = {0.0f, 0.0f, 0.0f, 1.0f},
    .specular  = {0.0f, 0.0f, 0.0f, 1.0f},
    .shininess = 0.0f
};
