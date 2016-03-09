#version 120

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

uniform mat4 transform;

void main()
{
	texCoord0 = texCoord;
	gl_Position = transform * vec4(position, 1.0);
}