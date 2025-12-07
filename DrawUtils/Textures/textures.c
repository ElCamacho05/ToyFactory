#include "textures.h"

#include <string.h>
#include <stdio.h>
#include <GL/glut.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

TEXTURE *woodTexture;
TEXTURE *wallTexture;

TEXTURE *loadTexture(const char *filename) {
    TEXTURE *newTexture = (TEXTURE *) malloc(sizeof(TEXTURE));
    if (!newTexture) return NULL;

    printf("Cargando textura: %s\n", filename);
    
    newTexture->data = stbi_load(filename, &(newTexture->width), &(newTexture->height), &(newTexture->nrChannels), 0); 
    
    if (newTexture->data) {
        printf("Textura cargada exitosamente: %dx%d canales: %d\n", newTexture->width, newTexture->height, newTexture->nrChannels);
        
        // Generate OpenGL texture
        glGenTextures(1, &(newTexture->id));
        glBindTexture(GL_TEXTURE_2D, newTexture->id);

        // Wrapping Config
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // Color Format
        GLenum format = (newTexture->nrChannels == 4) ? GL_RGBA : GL_RGB;

        // Upload to gpu
        glTexImage2D(GL_TEXTURE_2D, 0, format, newTexture->width, newTexture->height, 0, format, GL_UNSIGNED_BYTE, newTexture->data);
        
        // Free RAM, 
        // stbi_image_free(newTexture->data);
        newTexture->data = NULL; 
    } else {
        printf("FALLO al cargar textura: %s\n", filename);
        free(newTexture);
        return NULL;
    }

    return newTexture;
}

int genTexture(TEXTURE *texture) {
    glGenTextures(1, &(texture->id));
}

void boundTexture(TEXTURE *texture) {
    if (texture)
        glBindTexture(GL_TEXTURE_2D, texture->id);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texture->width, texture->height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture->data);
    // glGenerateMipmap(GL_TEXTURE_2D);
}

void freeTexture(TEXTURE *texture) {
    if (texture) {
        glDeleteTextures(1, &(texture->id));
        free(texture);
    }
}