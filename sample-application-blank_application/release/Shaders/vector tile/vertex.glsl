#version 330
//VectorTile: Vertex

in vec3 in_Vertex;
in int in_Type;

uniform mat4 projection;
uniform mat4 view;

uniform int highwaySize;
uniform int waySize;
uniform int defaultSize;

out vec2 v_type;

void main( void )
{
 	gl_Position = projection * view * vec4(in_Vertex, 1.0);
    v_type = vec2(in_Type);
}

