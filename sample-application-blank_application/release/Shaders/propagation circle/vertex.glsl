#version 330

in vec3 in_Vertex;
in vec2 in_UVs;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec2 uv;

void main( void )
{
 	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
    uv = in_UVs;
}

