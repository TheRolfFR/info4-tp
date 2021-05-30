#version 330
//RasterTile: Vertex

in vec3 in_Vertex;
in vec2 in_UV;

uniform mat4 projection;
uniform mat4 view;

out vec2 v_uv;

void main( void )
{
    gl_Position = projection * view * vec4(in_Vertex, 1.0);
    v_uv = in_UV;
}

