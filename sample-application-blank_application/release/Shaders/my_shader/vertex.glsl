#version 330
//VectorTile: Vertex

in vec3 in_Vertex;

uniform mat4 projection;
uniform mat4 view;

void main( void )
{
 	gl_Position = projection * view * vec4(in_Vertex, 1.0);
}

