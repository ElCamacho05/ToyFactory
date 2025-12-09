#ifndef TEXTURES_H
#define TEXTURES_H

#include "stb_image.h"

typedef struct texture {
    int id;
    int width;
    int height;
    int nrChannels;
    unsigned char *data;
} TEXTURE;

extern TEXTURE *whitePlanksTexture;
extern TEXTURE *whiteWoodTexture;
extern TEXTURE *darkPlanksTexture;
extern TEXTURE *darkWoodTexture;
extern TEXTURE *brickTexture;
extern TEXTURE *wallTexture;
extern TEXTURE *rubberTexture;
extern TEXTURE *beltTexture;
extern TEXTURE *whitePlasticPattern;
extern TEXTURE *blockyGold;
extern TEXTURE *cardboardTexture;

TEXTURE *loadTexture(const char *filename);
int genTexture(TEXTURE *texture);
void boundTexture(TEXTURE *texture);
void freeTexture(TEXTURE *texture);

#endif