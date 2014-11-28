/*
 * consoleIO.h
 *
 * Ficheiro cabecalho do modulo CONSOLEIO.
 *
 * J. Madeira - Out/2012
 */


#ifndef _consoleIO_h
#define _consoleIO_h


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


void infosConsola( void );

void infosModelo( int numVertices, GLfloat* arrayVertices );


#endif
