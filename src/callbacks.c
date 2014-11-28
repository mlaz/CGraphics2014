/*
 * callbacks.c
 *
 * J. Madeira - Out/2012
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


/* Callback functions */

void myDisplay( void )
{
   /* Limpar a janela */

   glClear( GL_COLOR_BUFFER_BIT );

   /* SHADERS */

   glUseProgram( programaGLSL );

   /* Input para o Vertex-Shader */

   glEnableVertexAttribArray( attribute_coord3d );

   /* Caracteristicas do array de coordenadas */

   glVertexAttribPointer( attribute_coord3d, // attribute

                          3,                 // number of elements per vertex, here (x,y,z)

                          GL_FLOAT,          // the type of each element

                          GL_FALSE,          // take our values as-is

                          0,                 // no extra data between each position

                          arrayVertices ); // pointer to the C array

    glEnableVertexAttribArray( attribute_corRGB );

   /* Caracteristicas do array de cores */

   glVertexAttribPointer( attribute_corRGB, // attribute

                          3,                 // number of elements per vertex, here (R,G,B)

                          GL_FLOAT,          // the type of each element

                          GL_FALSE,          // take our values as-is

                          0,                 // no extra data between each position

                          arrayCores ); // pointer to the C array

    /* Matriz global de transformacao */

    /* ATENCAO : Ordem das transformacoes !! */

    matrizGlobalTransf = matrizProj;

    RotateAboutX( &matrizGlobalTransf, DegreesToRadians( anguloRotXX ) );

    RotateAboutY( &matrizGlobalTransf, DegreesToRadians( anguloRotYY ) );

    RotateAboutZ( &matrizGlobalTransf, DegreesToRadians( anguloRotZZ ) );

    /* Diminuir o tamanho do modelo para nao sair fora do view volume */

    Scale( &matrizGlobalTransf, factorEscX, factorEscY, factorEscZ );

    /* For the vertex-shader, after the matrix is set */

    glUniformMatrix4fv( uniform_location_matriz_global, 1, GL_FALSE, matrizGlobalTransf.m);

    /* Push each element to the vertex shader */

    glDrawArrays( GL_TRIANGLE_STRIP, 0, numVertices );

    glDisableVertexAttribArray( attribute_coord3d );

    glDisableVertexAttribArray( attribute_corRGB );

    /* Display the result */

    /* DOUBLE-BUFFERING */

    glutSwapBuffers();
}


void myKeyboard( unsigned char key, int x, int y )
{
	/* Usar as teclas Q ou ESC para terminar o programa */

    /* Usar as teclar 1, 2, etc. para escolher o tipo de primitiva */

    switch( key )
    {
        case 'Q' :

        case 'q' :

        case 27  :  exit( EXIT_SUCCESS );

        case 'Z' :

        case 'z' :

            anguloRotZZ += 5;

            if( anguloRotZZ == 360.0 )
            {
                anguloRotZZ = 0.0;
            }

            glutPostRedisplay();

            break;

        case 'X' :

        case 'x' :

            anguloRotZZ -= 5;

            if( anguloRotZZ == -360.0 )
            {
                anguloRotZZ = 0.0;
            }

            glutPostRedisplay();

            break;

        case '+' :

            factorEscX *= 1.1;

            factorEscY *= 1.1;

            factorEscZ *= 1.1;

            glutPostRedisplay();

            break;

        case '-' :

            factorEscX *= 0.9;

            factorEscY *= 0.9;

            factorEscZ *= 0.9;

            glutPostRedisplay();

            break;
    }
}


void mySpecialKeys( int key, int x, int y )
{
	/* Usar as teclas de cursor para controlar as rotacoes */

    switch( key )
    {
        case GLUT_KEY_LEFT :

            anguloRotYY -= 5;

            if( anguloRotYY == -360.0 )
            {
                anguloRotYY = 0.0;
            }

            glutPostRedisplay();

            break;

        case GLUT_KEY_RIGHT :

            anguloRotYY += 5;

            if( anguloRotYY == 360.0 )
            {
                anguloRotYY = 0.0;
            }

            glutPostRedisplay();

            break;

        case GLUT_KEY_UP :

            anguloRotXX -= 5;

            if( anguloRotXX == -360.0 )
            {
                anguloRotXX = 0.0;
            }

            glutPostRedisplay();

            break;

        case GLUT_KEY_DOWN :

            anguloRotXX += 5;

            if( anguloRotXX == 360.0 )
            {
                anguloRotXX = 0.0;
            }

            glutPostRedisplay();

            break;
    }
}


void myMouse( int button, int state, int x, int y )
{
	/* Usar o botao direito para terminar o programa */

	if( ( state == GLUT_DOWN ) && ( button == GLUT_RIGHT_BUTTON ) )
    {
		exit( EXIT_SUCCESS );
	}
}


void registarCallbackFunctions( void )
{
   glutDisplayFunc( myDisplay );

   glutKeyboardFunc( myKeyboard );

   glutSpecialFunc( mySpecialKeys );

   glutMouseFunc( myMouse );
}
