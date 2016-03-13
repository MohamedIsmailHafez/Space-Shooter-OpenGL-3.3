#version 330

attribute vec3 position;
attribute vec2 texCoord;

varying vec2 texCoord0;

void main()
{
	texCoord0 = texCoord;
	
	vec2 vertexPosition_homoneneousspace = position.xy - vec2(640,360);

	vertexPosition_homoneneousspace /= vec2(640,360);

	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);
}