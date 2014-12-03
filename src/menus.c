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
 * menus.c
 *
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

                {"----------Quadrics----------", '-'},
                {"Ellipsoid",                    '1'},
				{"Sphere",                       '2'},
                {"Torus",                        '3'},
                {"Paraboloid",                   '4'},
				{"---------Functions---------",  '-'},
                {"f(x,y) = sen(y * a * cos(x))", '5'},
                {"z(x,y) = b * (x^2 + y^2)",     '6'},
                {"z(x,y) = x exp( - x^2 - y^2)", '7'},
                {"z(x,y) = a * sin(x) * cos(y)", '8'},
                {"---------------------------",  '-'},
                {"Change equation parameters"  , '9'}
};

int numItensMenu1 = sizeof( menu1 ) / sizeof( menuItemStruct );

/* Menu 2 - Botao Direito */

static menuItemStruct menu2[] = {

                {"------Projections------",  '-'},
                {"Parallel Projection",      'O'},
                {"Perspective Projection",   'P'},
                {"------Operations------",   '-'},
                {"Load Model",               'L'},
                {"Save Model",               'S'},
                {"----------------------",   '-'},
				{"Quit application",         '1'}
};

int numItensMenu2 = sizeof( menu2 ) / sizeof( menuItemStruct );


/* ----------------------------------------------------------------------- */

/* Callback function para o MENU 2 - Botao Direito */

static void myMenuEsq( int i )
{
	switch( menu1[i].val ) {

	case '1' :
        DrawEllipsoid(20,20, 1.0 , 1.0, 2.0, &numVertices, &arrayVertices, &arrayCores);
        activeMode=1;
		break;

	case '2' :
        DrawSphere(20,20, 1.0 , &numVertices, &arrayVertices, &arrayCores);
        activeMode=2;
		break;

    case '3':
        DrawTorus(20,20, 0.5, 1.0, &numVertices, &arrayVertices, &arrayCores);
        activeMode=3;
        break;

    case '4':
        DrawParaboloid(1, 0.5 , 500, &numVertices, &arrayVertices, &arrayCores);
        activeMode=4;
        break;

    case '5':
        DrawFunct1(1, &numVertices, &arrayVertices, &arrayCores);
        activeMode=5;
        break;

    case '6':
        DrawFunct2(0.5, &numVertices, &arrayVertices, &arrayCores);
        activeMode=6;
        break;

    case '7':
        DrawFunct3(10, &numVertices, &arrayVertices, &arrayCores);
        activeMode=7;
        break;

    case '8':
        DrawFunct4(3, &numVertices, &arrayVertices, &arrayCores);
        activeMode=8;
        break;

    case '9':
        if(activeMode==1)
        {
            double a,b,c;
            printf("Ellipsoid\nInsert radius A: ");
            scanf("%lf",&a);
            printf("Insert radius B: ");
            scanf("%lf",&b);
            printf("Insert radius C: ");
            scanf("%lf",&c);

            DrawEllipsoid(20,20, a , b, c, &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==2)
        {
            double a;
            printf("Sphere\nInsert radius: ");
            scanf("%lf",&a);

            DrawSphere(20,20, a , &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==3)
        {
            double a,b;
            printf("Torus\nInsert radius: ");
            scanf("%lf",&a);
            printf("Insert axial radius: ");
            scanf("%lf",&b);

            DrawTorus(20,20, a, b, &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==4)
        {
            double a;
            printf("Paraboloid\nInsert radius: ");
            scanf("%lf",&a);

            DrawParaboloid(a, 0.5 , 500, &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==5)
        {
            double a;
            printf("Function 1\nInsert factor: ");
            scanf("%lf",&a);

            DrawFunct1(a, &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==6)
        {
            double a;
            printf("Function 2\nInsert factor: ");
            scanf("%lf",&a);

            DrawFunct2(a, &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==7)
        {
            double a;
            printf("Function 3\nInsert factor: ");
            scanf("%lf",&a);

            DrawFunct3(a, &numVertices, &arrayVertices, &arrayCores);
        }

        else if(activeMode==8)
        {
            double a;
            printf("Function 4\nInsert factor: ");
            scanf("%lf",&a);

            DrawFunct4(a, &numVertices, &arrayVertices, &arrayCores);
        }

        else
        {
            printf("Unknown surface!");
        }

        break;

    }

	glutPostRedisplay();
}

static void myMenuDir( int i )
{
    char fileName[20];

	switch( menu2[i].val ) {

    case 'O' :

        matrizProj = IDENTITY_MATRIX;

        break;

    case 'P' :

        matrizProj = CreateProjectionMatrix( 60, 1, 1, 50 );

        /* Posicionar no interior do View Volome */

        Translate( &matrizProj, 0, 0, -5 );

        glutPostRedisplay();

        break;


    case 'L':
        printf("Name for the file you want to load: ");
        scanf("%s",fileName);

        lerDeFicheiro( fileName, &numVertices,  &arrayVertices, &arrayCores );

        glutPostRedisplay();

        break;

    case 'S':
        printf("Name for the file you want to save: ");
        scanf("%s",fileName);

        escreverEmFicheiro( fileName, numVertices,  &arrayVertices, &arrayCores );

        break;

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


