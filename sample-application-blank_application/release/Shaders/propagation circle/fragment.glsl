#version 330

in vec2 uv;

uniform vec4 color;

out vec4 outColor;

void main( void )
{
    outColor = color; 
    if (length((uv - 0.5)/2) > 0.25)
        discard;
}
