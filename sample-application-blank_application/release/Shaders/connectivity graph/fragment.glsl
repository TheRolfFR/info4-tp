#version 330

in vec2 v_uv;

uniform vec4 color_a;
uniform vec4 color_b;
out vec4 outColor;

void main( void )
{
 	outColor = v_uv.x * color_b + (1 - v_uv.x) * color_a;
}
