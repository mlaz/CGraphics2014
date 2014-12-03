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
 * 3dSurfaces.c
 *
 */


#include <stdlib.h>

#include <stdio.h>

#include <string.h>


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


#include "globals.h"

#include "callbacks.h"

#include "consoleIO.h"

#include "init.h"

#include "menus.h"

#include "shaders.h"


int main( int argc, char** argv )
{
   GLenum glewInitResult;

   /* Inicializacao do GLUT */

   glutInit( &argc, argv );

   inicializarJanela();

   /* Criar os menus */

   criarMenus();

   /* Inicializacao do GLEW */

   glewInitResult = glewInit();

   if( GLEW_OK != glewInitResult )
   {
        fprintf(

            stderr,

            "ERROR: %s\n",

            glewGetErrorString( glewInitResult )

        );

        exit( EXIT_FAILURE );
    }

    /* Qual a versao do OpenGL? */

    fprintf(

        stdout,

        "INFO: OpenGL Version: %s\n",

         glGetString( GL_VERSION )

    );

    /* Inicializar o estado da aplicacao */

    inicializarEstado();

    /* Inicializar os objectos a representar */

    inicializarModelos();

    /* Inicializar os shaders */

    if ( initResources() == 1 )
    {
        /* Registando callback functions se OK */

        registarCallbackFunctions();

        infosConsola();

        glutMainLoop();

   }

   /* Housekeeping */

   freeResources();

   libertarArraysGlobais();

   return EXIT_SUCCESS;
}
