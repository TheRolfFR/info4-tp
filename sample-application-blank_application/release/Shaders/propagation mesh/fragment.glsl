#version 330
//VectorTile: Fragment 

in float alpha;

uniform vec4 diffuse;
out vec4 outColor;

void main( void )
{
 	outColor = vec4(diffuse.xyz, alpha);
}
