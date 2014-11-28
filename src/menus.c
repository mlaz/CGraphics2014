/*
 * menus.c
 *
 * Ficheiro de implementacao do modulo MENUS.
 *
 * J. Madeira - Out/2012
 */


/* Incluir os ficheiros cabecalhos necessarios */

#include <stdlib.h>


#define GLEW_STATIC /* Necessario se houver problemas com a lib */

#include <GL/glew.h>

#include <GL/freeglut.h>


#include "consoleIO.h"

#include "globals.h"

#include "init.h"

#include "menus.h"

#include "models.h"


/* ----------------------------------------------------------------------- */

/* Definicao dos menus e sub-menus usando um tipo auxiliar e arrays */

/* Ref.: "OpenGL: A Primer" - p. 219-220 */

typedef struct menuItemStruct {

    char* item; /* O texto do item */

    char  val;  /* O valor retornado */

} menuItemStruct;

/* Menu 1 - Botao Esquerdo */

static menuItemStruct menu1[] = {

                {"Tetraedro",           '1'},
				{"Cubo",                '2'},
				{"--------------   ",   '-'},
				{"Proj. Paralela",      'O'},
				{"Proj. Perspectiva",   'P'}
};

int numItensMenu1 = sizeof( menu1 ) / sizeof( menuItemStruct );

/* Menu 2 - Botao Direito */

static menuItemStruct menu2[] = {

				{"Sair",          '1'}
};

int numItensMenu2 = sizeof( menu2 ) / sizeof( menuItemStruct );


/* ----------------------------------------------------------------------- */

/* Callback function para o MENU 2 - Botao Direito */

static void myMenuEsq( int i )
{
	switch( menu1[i].val ) {

	case '1' :

        libertarArraysGlobais();

        lerDeFicheiro( "tetraedro.txt", &numVertices, &arrayVertices, &arrayCores );

        /* Valores iniciais dos parametros das transformacoes */

        anguloRotXX = 0;

        anguloRotYY = 0;

        anguloRotZZ = 0;

        factorEscX = 0.3;

        factorEscY = 0.3;

        factorEscZ = 0.3;

		break;

	case '2' :

        libertarArraysGlobais();

        lerDeFicheiro( "cubo.txt", &numVertices, &arrayVertices, &arrayCores );

        /* Valores iniciais dos parametros das transformacoes */

        anguloRotXX = 0;

        anguloRotYY = 0;

        anguloRotZZ = 0;

        factorEscX = 0.3;

        factorEscY = 0.3;

        factorEscZ = 0.3;

		break;

	case 'O' :

        matrizProj = IDENTITY_MATRIX;

		break;

	case 'P' :

        matrizProj = CreateProjectionMatrix( 60, 1, 1, 50 );

        /* Posicionar no interior do View Volome */

        Translate( &matrizProj, 0, 0, -5 );

        glutPostRedisplay();

		break;
	}

	glutPostRedisplay();
}

static void myMenuDir( int i )
{
	switch( menu2[i].val ) {

	case '1' :

        exit( EXIT_SUCCESS );

		break;
	}
}

/* Criar os menus */

void criarMenus( void )
{
    int i;

    /* MENU 1 */

	glutCreateMenu( myMenuEsq );

    for( i=0; i<numItensMenu1; i++ )
    {
	    /* Os itens do menu e os valores devolvidos a funcao callback */

        glutAddMenuEntry( menu1[i].item, i );
	}

	/* O botao do rato associado */

	glutAttachMenu( GLUT_LEFT_BUTTON );

    /* MENU 2 */

	glutCreateMenu( myMenuDir );

    for( i=0; i<numItensMenu2; i++ )
    {
	    /* Os itens do menu e os valores devolvidos a funcao callback */

        glutAddMenuEntry( menu2[i].item, i );
	}

	/* O botao do rato associado */

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}


/* ----------------------------------------------------------------------- */


