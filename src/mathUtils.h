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
 * mathUtils.h
 *
 */


#ifndef _math_utils_h
#define _math_utils_h

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static const double PI = 3.14159265358979323846;

typedef struct Matrix
{
	float m[16];
} mat4x4;

static const mat4x4 IDENTITY_MATRIX = { {
	1, 0, 0, 0,
	0, 1, 0, 0,
	0, 0, 1, 0,
	0, 0, 0, 1
} };

float Cotangent(float angle);

float DegreesToRadians(float degrees);

float RadiansToDegrees(float radians);

mat4x4* MultiplyMatrices(const mat4x4* m1, const mat4x4* m2);

void RotateAboutX(mat4x4* m, float angle);

void RotateAboutY(mat4x4* m, float angle);

void RotateAboutZ(mat4x4* m, float angle);

void Scale(mat4x4* m, float x, float y, float z);

void Translate(mat4x4* m, float x, float y, float z);

mat4x4 CreateProjectionMatrix( float fovy,

                               float aspect_ratio,

                               float near_plane,

                               float far_plane );


#endif
