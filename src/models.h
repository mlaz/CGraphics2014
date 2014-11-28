/*
 * models.h
 *
 * Ficheiro cabecalho do modulo MODELS.
 *
 * J. Madeira - Out/2012
 */


#ifndef _models_h
#define _models_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


void lerDeFicheiro( char* nome, int* numVertices, GLfloat** arrayVertices, GLfloat** arrayCores );

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
#endif
