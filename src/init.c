/*
 * init.c
 *
 * Ficheiro de implementacao do modulo INIT.
 *
 * J. Madeira - Out/2012
 */


#include <stdlib.h>

#include <stdio.h>

#include <string.h>


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


#include "globals.h"

#include "mathUtils.h"

#include "models.h"


void inicializarEstado( void )
{

   /* DOUBLE-BUFFERING */

   glutInitDisplayMode (GLUT_DOUBLE);

   /* Definir a cor do fundo */

   glClearColor( 0.0, 0.0, 0.0, 1.0 );

   /* Back-Face Culling */

   glCullFace( GL_BACK );

   glEnable( GL_CULL_FACE );

   /* Matriz de projeccao é inicialmente a IDENTIDADE => Proj. Paralela Ortogonal */

   // matrizProj = IDENTITY_MATRIX;

   //Start with perspective projection
   matrizProj = CreateProjectionMatrix( 60, 1, 1, 50 );
   Translate( &matrizProj, 0, 0, -5 );

   /* Parametros das transformacoes */

   anguloRotXX = 0;

   anguloRotYY = 0;

   anguloRotZZ = 0;

   factorEscX = 0.5;

   factorEscY = 0.5;

   factorEscZ = 0.5;
}


void inicializarJanela( void )
{
   /* Caracteristicas da janela de saida */

   glutInitWindowSize( 800, 800 ); /* Usar variaveis GLOBAIS para estes parametros */

   glutInitWindowPosition( 200, 0 );

   /* Para terminar de modo apropriado */

   glutSetOption(

        GLUT_ACTION_ON_WINDOW_CLOSE,

        GLUT_ACTION_GLUTMAINLOOP_RETURNS

    );

   /* Criar a janela de saida */

   windowHandle = glutCreateWindow( "3D Surfaces" );
   //Fullscreen mode
   // glutEnterGameMode();

   if( windowHandle < 1 )
   {
        fprintf(

             stderr,

             "ERROR: Could not create a new rendering window.\n"

         );

         exit( EXIT_FAILURE );
   }
}

void inicializarModelos( void )
{
  //Default view
  DrawEllipsoid(20,20, 1.0 , 1.0, 2.0, &numVertices, &arrayVertices, &arrayCores);
  activeMode=1;
}

void libertarArraysGlobais( void )
{
    free( arrayVertices );

    free( arrayCores );
}
