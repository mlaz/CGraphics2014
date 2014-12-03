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
 * consoleIO.h
 *
 */


#ifndef _consoleIO_h
#define _consoleIO_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


void infosConsola( void );

void infosModelo( int numVertices, GLfloat* arrayVertices );


#endif
