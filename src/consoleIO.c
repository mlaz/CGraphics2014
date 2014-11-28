/*
 * consoleIO.c
 *
 * Ficheiro de implementacao do modulo CONSOLEIO.
 *
 * J. Madeira - Out/2012
 */


/* Incluir os ficheiros cabecalhos necessarios */


#include <stdio.h>

#include "consoleIO.h"


/* Escrever algumas informacoes na consola */

void infosConsola( void )
{
	fprintf( stdout, "\n Para Terminar: usar as teclas Q ou ESC\n\n");
}


void infosModelo( int numVertices, GLfloat* arrayVertices )
{
    int i;

    int j;

    fprintf( stdout, "Numero de Vertices = %d\n", numVertices );

    for( i = 0; i < numVertices; i++ )
    {
        for( j = 0; j < 3; j++ )
        {
            fprintf( stdout, "%f ", arrayVertices[ 3 * i + j ] );
        }

        fprintf( stdout, "\n" );
    }
}



