#version 120

attribute vec3 coord3d;

attribute vec3 v_corRGB;

uniform mat4x4 matriz;

varying vec3 f_corRGB; 

void main( void )
{
    gl_Position = matriz * vec4( coord3d, 1.0 );

    f_corRGB = v_corRGB;
}
