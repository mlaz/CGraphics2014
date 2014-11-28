/*
 * mathUtils.c
 *
 * Ficheiro de implementacao do modulo MATH_UTILS.
 *
 * Referencia: http://openglbook.com/the-book/chapter-4-entering-the-third-dimension/
 *
 *             Copyright (C) 2011 by Eddy Luten
 *
 *             Permission is hereby granted, free of charge, to any person obtaining a copy
 *	           of this software and associated documentation files (the "Software"), to deal
 *             in the Software without restriction, including without limitation the rights
 *             to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *             copies of the Software, and to permit persons to whom the Software is
 *             furnished to do so, subject to the following conditions:
 *
 *             The above copyright notice and this permission notice shall be included in
 *             all copies or substantial portions of the Software.
 *
 * J. Madeira - Out/2012
 */


#include <math.h>

#include <string.h>


#include "mathUtils.h"


float Cotangent(float angle)
{
    return (float)(1.0 / tan(angle));
}

float DegreesToRadians(float degrees)
{
	return degrees * (float)(PI / 180.0);
}


float RadiansToDegrees(float radians)
{
	return radians * (float)(180.0 / PI);
}


mat4x4* MultiplyMatrices(const mat4x4* m1, const mat4x4* m2)
{
	unsigned int row, column;

	mat4x4* out = (mat4x4*) malloc( sizeof( struct Matrix ));

	for (row = 0; row < 4; ++row)
		for (column = 0; column < 4; ++column)

		    /* Correccao para multiplicar a direita - J. Madeira */

			out->m[column * 4 + row] =
				(m1->m[row + 0] * m2->m[column * 4 + 0]) +
				(m1->m[row + 4] * m2->m[column *4 + 1]) +
				(m1->m[row + 8] * m2->m[column *4 + 2]) +
				(m1->m[row + 12] * m2->m[column *4 + 3]);

	return out;
}


void RotateAboutX(mat4x4* m, float angle)
{
	mat4x4 rotation = IDENTITY_MATRIX;

	float sine = (float)sin(angle);

	float cosine = (float)cos(angle);

	rotation.m[5] = cosine;

	rotation.m[6] = sine;

	rotation.m[9] = -sine;

	rotation.m[10] = cosine;

	memcpy(m->m, MultiplyMatrices(m, &rotation)->m, sizeof(m->m));
}


void RotateAboutY(mat4x4* m, float angle)
{
	mat4x4 rotation = IDENTITY_MATRIX;

	float sine = (float)sin(angle);

	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;

	rotation.m[8] = sine;

	rotation.m[2] = -sine;

	rotation.m[10] = cosine;

	memcpy(m->m, MultiplyMatrices(m, &rotation)->m, sizeof(m->m));
}


void RotateAboutZ(mat4x4* m, float angle)
{
	mat4x4 rotation = IDENTITY_MATRIX;

	float sine = (float)sin(angle);

	float cosine = (float)cos(angle);

	rotation.m[0] = cosine;

	rotation.m[1] = sine;

	rotation.m[4] = -sine;

	rotation.m[5] = cosine;

	memcpy(m->m, MultiplyMatrices(m, &rotation)->m, sizeof(m->m));
}


void Scale( mat4x4* m, float x, float y, float z )
{
	mat4x4 scale = IDENTITY_MATRIX;

	scale.m[0] = x;

	scale.m[5] = y;

	scale.m[10] = z;

	memcpy(m->m, MultiplyMatrices(m, &scale)->m, sizeof(m->m));
}


void Translate(mat4x4* m, float x, float y, float z)
{
    mat4x4 translation = IDENTITY_MATRIX;

    translation.m[12] = x;

    translation.m[13] = y;

    translation.m[14] = z;

    memcpy(m->m, MultiplyMatrices(m, &translation)->m, sizeof(m->m));
}


mat4x4 CreateProjectionMatrix( float fovy,

                               float aspect_ratio,

                               float near_plane,

                               float far_plane )
{
    mat4x4 out = { { 0 } };

    const float y_scale = Cotangent(DegreesToRadians(fovy / 2));

    const float x_scale = y_scale / aspect_ratio;

    const float frustum_length = far_plane - near_plane;

    out.m[0] = x_scale;

    out.m[5] = y_scale;

    out.m[10] = -((far_plane + near_plane) / frustum_length);

    out.m[11] = -1;

    out.m[14] = -((2 * near_plane * far_plane) / frustum_length);

    return out;
}


