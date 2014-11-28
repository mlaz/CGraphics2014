/*
 * models.c
 *
 * Ficheiro de implementacao do modulo MODELS.
 *
 * J. Madeira - Out/2012
 */


/* Incluir os ficheiros cabecalhos necessarios */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mathUtils.h"
#include "models.h"


/* Ler um modelo de ficheiro */

/* FORMATO SIMPLES: x y z R G B */

/* VERTICES REPLICADOS */

/* Atribuida MEMORIA aos arrays */

/* Nao sao verificados erros de formatacao do ficheiro */

void lerDeFicheiro( char* nome, int* numVertices, GLfloat** arrayVertices, GLfloat** arrayCores )
{
  int i;

  int j;

  int n;

  int indexArrayCoords;

  int indexArrayRGB;

  GLfloat* coordenadas;

  GLfloat* cores;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  FILE* fp = fopen( nome, "r");

  if ( fp == NULL )
    {
      fprintf( stderr, "ERRO na leitura do ficheiro %s\n", nome );

      exit( EXIT_FAILURE );
    }

  /* Ler o numero de vertices */

  fscanf( fp, "%d", &n );

  *numVertices = n;

  /* Criar os arrays */

  /* Coordenadas ( x, y, z ) dos vertices */

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;

  /* Ler a informacao de cada vertice */

  indexArrayCoords = 0;

  indexArrayRGB = 0;

  for( i = 0; i < n; i++ )
    {
      for( j = 0; j < 3; j++ )
        {
          fscanf( fp, "%f", &( coordenadas[ indexArrayCoords++ ] ) );
        }

      for( j = 0; j < 3; j++ )
        {
          fscanf( fp, "%f", &( cores[ indexArrayRGB++ ] ) );
        }
    }

  fclose( fp );
}

void DrawEllipsoid(unsigned int uiStacks,
                   unsigned int uiSlices,
                   float fA, float fB, float fC,
                   int* numVertices,
                   GLfloat** arrayVertices, GLfloat** arrayCores)
{
  GLfloat* coordenadas;

  GLfloat* cores;

  float tStep = (PI) / (float)uiSlices;
  float sStep = (PI) / (float)uiStacks;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  int ntstep =  (((PI/2)+.0001 + PI/2) / tStep) + 1;
  int nsstep = ((PI+.0001 + PI) / sStep) + 1;
  int n = ntstep * nsstep * 2;

  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;

  float t;
  float s;
  int idx = 0;
  for(t = -PI/2; t <= (PI/2)+.0001; t += tStep)
    {
      for(s = -PI; s <= PI+.0001; s += sStep)
        {
          coordenadas[idx] = fA * cos(t) * cos(s); //x
          cores[idx] = 0.0; //r
          idx++;
          coordenadas[idx] = fB * cos(t) * sin(s); //y
          cores[idx] = 0.0; //g
          idx++;
          coordenadas[idx] = fC * sin(t); //z
          cores[idx] = 1.0; //b
          idx++;

          coordenadas[idx] = fA * cos(t+tStep) * cos(s); //x
          cores[idx] = 0.0; //r
          idx++;
          coordenadas[idx] = fB * cos(t+tStep) * sin(s); //y
          cores[idx] = 0.0; //g
          idx++;
          coordenadas[idx] = fC * sin(t+tStep); //z
          cores[idx] = 1.0; //b
          idx++;
        }
    }

}


void DrawSphere(unsigned int uiStacks,
                unsigned int uiSlices,
                float radius,
                int* numVertices,
                GLfloat** arrayVertices, GLfloat** arrayCores)
{
  GLfloat* coordenadas;

  GLfloat* cores;

  float tStep = (PI) / (float)uiSlices;
  float sStep = (PI) / (float)uiStacks;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  int ntstep =  (((PI/2)+.0001 + PI/2) / tStep) + 1;
  int nsstep = ((PI+.0001 + PI) / sStep) + 1;
  int n = ntstep * nsstep * 2;

  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;

  float t;
  float s;
  int idx = 0;
  for(t = -PI/2; t <= (PI/2)+.0001; t += tStep)
    {
      for(s = -PI; s <= PI+.0001; s += sStep)
        {
          coordenadas[idx] = radius * cos(t) * cos(s); //x
          cores[idx] = 0.0; //r
          idx++;
          coordenadas[idx] = radius * cos(t) * sin(s); //y
          cores[idx] = 0.0; //g
          idx++;
          coordenadas[idx] = radius * sin(t); //z
          cores[idx] = 1.0; //b
          idx++;

          coordenadas[idx] = radius * cos(t+tStep) * cos(s); //x
          cores[idx] = 0.0; //r
          idx++;
          coordenadas[idx] = radius * cos(t+tStep) * sin(s); //y
          cores[idx] = 0.0; //g
          idx++;
          coordenadas[idx] = radius * sin(t+tStep); //z
          cores[idx] = 1.0; //b
          idx++;
        }
    }
}

void DrawTorus(unsigned int uiStacks,
               unsigned int uiSlices,
               float radius,
               float raxial,
               int* numVertices,
               GLfloat** arrayVertices, GLfloat** arrayCores)
{
  GLfloat* coordenadas;

  GLfloat* cores;

  float tStep = (PI) / (float)uiSlices;
  float sStep = (PI) / (float)uiStacks;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  int ntstep = ((PI+.0001 + PI) / tStep) + 1;
  int nsstep = ((PI+.0001 + PI) / sStep) + 1;
  int n = ntstep * nsstep * 2;

  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;

  float t;
  float s;
  int idx = 0;
  for(t = -PI; t <= PI+.0001; t += tStep)
    {
      for(s = -PI; s <= PI+.0001; s += sStep)
        {
          coordenadas[idx] = (raxial + (radius * cos(t))) * cos(s); //x
          cores[idx] = 0.0; //r
          idx++;
          coordenadas[idx] = (raxial + (radius * cos(t))) * sin(s); //y
          cores[idx] = 0.0; //g
          idx++;
          coordenadas[idx] = radius * sin(t); //z
          cores[idx] = 1.0; //b
          idx++;

          coordenadas[idx] = (raxial + (radius * cos(t + tStep))) * cos(s); //x
          cores[idx] = 0.0; //r
          idx++;
          coordenadas[idx] = (raxial + (radius * cos(t + tStep))) * sin(s); //y
          cores[idx] = 0.0; //g
          idx++;
          coordenadas[idx] = radius * sin(t + tStep); //z
          cores[idx] = 1.0; //b
          idx++;
        }
    }
}
