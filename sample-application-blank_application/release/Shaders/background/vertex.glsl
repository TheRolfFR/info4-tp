#version 330

in vec3 in_Vertex;

void main( void )
{
 	gl_Position = vec4(in_Vertex, 1.0);
}

