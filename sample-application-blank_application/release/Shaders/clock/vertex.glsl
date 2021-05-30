#version 330
//Clock: vertex

in vec3 in_Vertex;
in vec2 in_UV;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 uv;

void main( void )
{
    uv = in_UV;
    uv.y = 1 - uv.y;
 	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

