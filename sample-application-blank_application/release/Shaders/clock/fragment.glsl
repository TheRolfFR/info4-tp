#version 330
//Clock: fragment 

in vec2 uv;

uniform vec4 diffuse;
uniform sampler2D tex;
out vec4 outColor;

void main( void )
{
 	outColor = texture(tex, uv).r * diffuse;
}
