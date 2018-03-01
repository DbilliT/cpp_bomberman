#version 120

uniform	mat4 projection;
uniform	mat4 view;
uniform	mat4 model;

uniform sampler2D fTexture0;

varying vec4 fColor;
varying vec4 fNormal;
varying vec2 fUv;
varying float f;

void main(void)
{
	vec4 color = texture2D(fTexture0, fUv) * fColor;
	color.x *= f;
	color.y *= f;
	color.z *= f;
	gl_FragColor = color;
}
