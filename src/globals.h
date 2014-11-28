/*
 * globals.h
 *
 * Declaracao de tipos e variaveis globais.
 *
 * J. Madeira - Out/2012
 *
 */


#ifndef _globals_h
#define _globals_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


#include "mathUtils.h"


/* Variaveis GLOBAIS !! */

int windowHandle;

/* O identificador do programa em GLSL combinando os SHADERS */

GLuint programaGLSL;

/* Os identificadores dos SHADERS */

GLuint vs;

GLuint fs;

/* Para passar coordenadas, cores a a matriz de transformacao ao Vertex-Shader */

GLint attribute_coord3d;

GLint attribute_corRGB;

GLint uniform_location_matriz_global;

/* Coordenadas dos vertices */

GLsizei numVertices;

GLfloat* arrayVertices;

/* Cores das faces */

GLfloat* arrayCores;

/* Matriz de projeccao */

mat4x4 matrizProj;

/* Matriz global de transformacao */

mat4x4 matrizGlobalTransf;

/* Parametros das transformacoes */

GLfloat anguloRotXX;

GLfloat anguloRotYY;

GLfloat anguloRotZZ;

GLfloat factorEscX;

GLfloat factorEscY;

GLfloat factorEscZ;

#endif
