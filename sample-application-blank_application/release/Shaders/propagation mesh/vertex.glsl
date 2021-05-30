#version 330
//VectorTile: Vertex 

in vec3 in_Vertex;
in float in_Alpha;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out float alpha;

void main( void )
{
    alpha = in_Alpha;
 	gl_Position = projection * view * model * vec4(in_Vertex, 1.0);
}

