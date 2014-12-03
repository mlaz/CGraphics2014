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
 * models.c
 *
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

void escreverEmFicheiro( char* nome, int numVertices, GLfloat** arrayVertices, GLfloat** arrayCores )
{
  int i;

  int j;

  int n;

  int indexArrayCoords;

  int indexArrayRGB;

  GLfloat* coordenadas;

  GLfloat* cores;

  int writeInFile=0;
  char *option;

  //File exists
  if(fileExists(nome))
  {
    do
    {
      printf("File already exists. Would you like to overwrite (y/n)? ");
      scanf("%s",option);

      if(option[0]!='y' && option[0]!='y' && option[0]!='n' && option[0]!='N'){
        printf("Invalid option. Try again!\n");
      }
    }
    while(option[0]!='y' && option[0]!='y' && option[0]!='n' && option[0]!='N');
    
    fflush(stdout);

    //Overwrite file
    if (option[0]=='y' || option[0]=='Y')
    {
      writeInFile=1;

    }

    //This condition has to be here, otherwise gives Bus Error
    else
    {
      //nothing to do
    }


  }

  //File doesnt exists
  else
  {
    writeInFile=1;
  }

  //Write in the file
  if(writeInFile)
  {
    fflush(stdout);
    FILE* fp = fopen( nome, "w");

    if ( fp == NULL )
      {
        fprintf( stderr, "ERRO na leitura do ficheiro %s\n", nome );

        exit( EXIT_FAILURE );
      }

    /* Escrever o numero de vertices */
    n = numVertices;
    fprintf( fp, "%d\n", n );

    /* Escrever a informacao de cada vertice */

    cores = *arrayCores;
    coordenadas = *arrayVertices;

    indexArrayCoords = 0;

    indexArrayRGB = 0;

    for( i = 0; i < n; i++ )
      {
        for( j = 0; j < 3; j++ )
          {
            fprintf( fp, "%f", coordenadas[ indexArrayCoords++ ] );
            fprintf( fp, " ");
          }

        for( j = 0; j < 3; j++ )
          {
            fprintf( fp, "%f",  cores[ indexArrayRGB++ ] );
            fprintf( fp, " ");
          }
        fprintf( fp, "\n");
      }

    fclose( fp );
  }
  
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

void DrawParaboloid(GLfloat radius,
                    GLfloat A,
                    unsigned precession,
                    int* numVertices,
                    GLfloat** arrayVertices,
                    GLfloat** arrayCores)
{
  GLfloat* coordenadas;

  GLfloat* cores;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  unsigned levels = precession / 25;
  unsigned point_on_level = precession / levels;

  GLfloat height = radius * 2;
  GLfloat height_delta = height / levels;
  GLfloat base = -radius;

  GLfloat radius_angle_delta = 2 * PI /( (float) point_on_level);

  int n = levels * point_on_level * 2 + 1;

  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;
  GLfloat phi;
  GLfloat cradius;
  int idx = 0;
  unsigned int i;
  unsigned int j;

  for(i = 0; i < levels; ++i)
    {
    for(j = 0; j < point_on_level; ++j)
      {
      phi = j * radius_angle_delta;
      coordenadas[idx + 2] = height_delta * i;
      cradius = A * sqrt(coordenadas[idx + 2]);
      coordenadas[idx + 2] += base;
      coordenadas[idx] = cradius * cos(phi);
      coordenadas[idx + 1] = cradius * sin(phi);
      cores[idx] = 0.0;
      cores[idx + 1] = 0.0;
      cores[idx + 2] = 1.0;
      idx += 3;

      phi = j * radius_angle_delta;
      coordenadas[idx + 2] = height_delta * (i + 1);
      cradius = A * sqrt(coordenadas[idx + 2]);
      coordenadas[idx + 2] += base;
      coordenadas[idx] = cradius * cos(phi);
      coordenadas[idx + 1] = cradius * sin(phi);
      cores[idx] = 0.0;
      cores[idx + 1] = 0.0;
      cores[idx + 2] = 1.0;
      idx += 3;
    }
  }
  phi = j * radius_angle_delta;
  coordenadas[idx + 2] = height_delta * i;
  cradius = A * sqrt(coordenadas[idx + 2]);
  coordenadas[idx + 2] += base;
  coordenadas[idx] = cradius * cos(phi);
  coordenadas[idx + 1] = cradius * sin(phi);
  cores[idx] = 0.0;
  cores[idx + 1] = 0.0;
  cores[idx + 2] = 1.0;
}

//f(x,y) = sen(y * a * cos(x))
void DrawFunct1(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores)
{

  GLfloat* coordenadas;

  GLfloat* cores;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  GLfloat levels = 10;

  GLfloat stepsize = 0.1;

  int n = 20503;
  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;
  GLfloat i;
  GLfloat j;
  unsigned int idx = 0;
  int npontos = 0;
  int increm = 1;
  for(i = (float) -(levels/2); i <= (float) levels/2; i += stepsize)
    {
      if (increm == 1)
        {
          for(j =  (float) -(levels/2); j <=  (float) levels/2; j += stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = sin(coordenadas[idx + 1] * factor * cos(coordenadas[idx]));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = sin(coordenadas[idx + 1] * factor * cos(coordenadas[idx]));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j - stepsize);
          coordenadas[idx + 2] = sin(coordenadas[idx + 1] * factor * cos(coordenadas[idx]));

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 0;
        }
      else
        {
          for(j = (float) levels/2; j >= (float) (-levels/2); j -= stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = sin(coordenadas[idx + 1] * factor * cos(coordenadas[idx]));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = sin(coordenadas[idx + 1] * factor *cos(coordenadas[idx]));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j + stepsize);
          coordenadas[idx + 2] = sin(coordenadas[idx + 1] * factor * cos(coordenadas[idx]));

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 1;
        }
    }
  /* printf("npontos: %d", npontos); */
  /* printf("\n"); */
  /* fflush (stdout); */
}

void DrawFunct2(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores)
{

  GLfloat* coordenadas;

  GLfloat* cores;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  GLfloat levels = 10;

  GLfloat stepsize = 0.1;

  int n = 20503;
  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;
  GLfloat i;
  GLfloat j;
  unsigned int idx = 0;
  int npontos = 0;
  int increm = 1;
  for(i = (float) -(levels/2); i <= (float) levels/2; i += stepsize)
    {
      if (increm == 1)
        {
          for(j =  (float) -(levels/2); j <=  (float) levels/2; j += stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = (pow(coordenadas[idx], 2) + pow(coordenadas[idx+1], 2)) * factor;

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = (pow(coordenadas[idx], 2) + pow(coordenadas[idx+1], 2)) * factor;

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j - stepsize);
          coordenadas[idx + 2] = (pow(coordenadas[idx], 2) + pow(coordenadas[idx+1], 2)) * factor;

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 0;
        }
      else
        {
          for(j = (float) levels/2; j >= (float) (-levels/2); j -= stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = (pow(coordenadas[idx], 2) + pow(coordenadas[idx+1], 2)) * factor;

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = (pow(coordenadas[idx], 2) + pow(coordenadas[idx+1], 2)) * factor;

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j + stepsize);
          coordenadas[idx + 2] = (pow(coordenadas[idx], 2) + pow(coordenadas[idx+1], 2)) * factor;

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 1;
        }
    }
  /* printf("npontos: %d", npontos); */
  /* printf("\n"); */
  /* fflush (stdout); */
}

//z(x,y) = x exp( - x^2 - y^2)
void DrawFunct3(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores)
{

  GLfloat* coordenadas;

  GLfloat* cores;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  GLfloat levels = 10;

  GLfloat stepsize = 0.1;

  int n = 20503;
  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;
  GLfloat i;
  GLfloat j;
  unsigned int idx = 0;
  int npontos = 0;
  int increm = 1;
  for(i = (float) -(levels/2); i <= (float) levels/2; i += stepsize)
    {
      if (increm == 1)
        {
          for(j =  (float) -(levels/2); j <=  (float) levels/2; j += stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = factor * coordenadas[idx] * exp( (-pow(coordenadas[idx], 2) - pow(coordenadas[idx+1], 2)));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = factor * coordenadas[idx] * exp( (-pow(coordenadas[idx], 2) - pow(coordenadas[idx+1], 2)));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j - stepsize);
          coordenadas[idx + 2] = factor * coordenadas[idx] * exp( (-pow(coordenadas[idx], 2) - pow(coordenadas[idx+1], 2)));

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 0;
        }
      else
        {
          for(j = (float) levels/2; j >= (float) (-levels/2); j -= stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = factor * coordenadas[idx] * exp( (-pow(coordenadas[idx], 2) - pow(coordenadas[idx+1], 2)));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] = factor * coordenadas[idx] * exp( (-pow(coordenadas[idx], 2) - pow(coordenadas[idx+1], 2)));

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j + stepsize);
          coordenadas[idx + 2] = factor * coordenadas[idx] * exp( (-pow(coordenadas[idx], 2) - pow(coordenadas[idx+1], 2)));

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 1;
        }
    }
  /* printf("npontos: %d", npontos); */
  /* printf("\n"); */
  /* fflush (stdout); */
}

//z(x,y) = a * sin(x) * cos(y)
void DrawFunct4(GLfloat factor,
                int* numVertices,
                GLfloat** arrayVertices,
                GLfloat** arrayCores)
{

  GLfloat* coordenadas;

  GLfloat* cores;

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  GLfloat levels = 10;

  GLfloat stepsize = 0.1;

  int n = 20503;
  *numVertices = n;

  *arrayVertices = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  coordenadas = *arrayVertices;

  /* Cores ( R, G, B ) dos vertices */

  *arrayCores = (GLfloat*) malloc( 3 * n * sizeof( GLfloat ) );

  cores = *arrayCores;
  GLfloat i;
  GLfloat j;
  unsigned int idx = 0;
  int npontos = 0;
  int increm = 1;
  for(i = (float) -(levels/2); i <= (float) levels/2; i += stepsize)
    {
      if (increm == 1)
        {
          for(j =  (float) -(levels/2); j <=  (float) levels/2; j += stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] =  factor * sin(coordenadas[idx]) * cos(coordenadas[idx+1]);

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] =  factor * sin(coordenadas[idx]) * cos(coordenadas[idx+1]);

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j - stepsize);
          coordenadas[idx + 2] =  factor * sin(coordenadas[idx]) * cos(coordenadas[idx+1]);

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 0;
        }
      else
        {
          for(j = (float) levels/2; j >= (float) (-levels/2); j -= stepsize)
            {
              coordenadas[idx] = (float) i;
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] =  factor * sin(coordenadas[idx]) * cos(coordenadas[idx+1]);

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;

              coordenadas[idx] = (float) (i + stepsize);
              coordenadas[idx + 1] = (float) j;
              coordenadas[idx + 2] =  factor * sin(coordenadas[idx]) * cos(coordenadas[idx+1]);

              cores[idx] = 0.0;
              cores[idx + 1] = 0.0;
              cores[idx + 2] = 1.0;
              idx += 3;
              npontos += 2;
            }
          coordenadas[idx] = (float) i;
          coordenadas[idx + 1] = (float) (j + stepsize);
          coordenadas[idx + 2] =  factor * sin(coordenadas[idx]) * cos(coordenadas[idx+1]);

          cores[idx] = 0.0;
          cores[idx + 1] = 0.0;
          cores[idx + 2] = 1.0;
          idx += 3;
          npontos += 1;
          increm = 1;
        }
    }
  /* printf("npontos: %d", npontos); */
  /* printf("\n"); */
  /* fflush (stdout); */
}

int fileExists(const char *fname)
{
    FILE *file;
    if ((file = (fopen(fname, "r"))))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
