#version 330
//RasterTile: Fragment 

in vec2 v_uv;

uniform sampler2D tileTexture;
uniform int tileTexture_ready;

out vec4 outColor;

void main( void )
{
    outColor = vec4(texture(tileTexture, v_uv).rgb, texture(tileTexture, v_uv).a*0.5);
}
