/*
 * Computação Visual 2014/2015
 *
 * OpenGL
 *
 * ############################
 *
 * Authors:
 *
 * Pedro Amaral, 46370
 * Miguel Azevedo, 38569
 *
 * ############################
 *
 * models.h
 *
 */


#ifndef _models_h
#define _models_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


void lerDeFicheiro( char* nome, int* numVertices, GLfloat** arrayVertices, GLfloat** arrayCores );

void escreverEmFicheiro( char* nome, int numVertices, GLfloat** arrayVertices, GLfloat** arrayCores );

void DrawEllipsoid(unsigned int uiStacks,
                   unsigned int uiSlices,
                   float fA, float fB, float fC,
                   int* numVertices,
                   GLfloat** arrayVertices, GLfloat** arrayCores);

void DrawSphere(unsigned int uiStacks,
                unsigned int uiSlices,
                float radius,
                int* numVertices,
                GLfloat** arrayVertices, GLfloat** arrayCores);

void DrawTorus(unsigned int uiStacks,
               unsigned int uiSlices,
               float radius,
               float raxial,
               int* numVertices,
               GLfloat** arrayVertices, GLfloat** arrayCores);

void DrawParaboloid(GLfloat radius,
                    GLfloat A,
                    unsigned precession,
                    int* numVertices,
                    GLfloat** arrayVertices,
                    GLfloat** arrayCores);

void DrawFunct1(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores);

void DrawFunct2(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores);

void DrawFunct3(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores);

void DrawFunct4(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores);

int fileExists(const char *fname);

#endif
