#version 330
//RasterTile: Fragment 

in vec2 v_uv;

uniform int time;

uniform vec4 tileColor;
uniform sampler2D tileTexture;
uniform int tileTexture_ready;

uniform sampler2D loadingTexture;

out vec4 outColor;

void main( void )
{
/*    outColor = tileColor;
    if (tileTexture_ready < 1)
    {
        float angle = -mod(time/100, 10) * (2*3.14)/10;
        float cos_factor = cos(angle), sin_factor = sin(angle);
        mat2 rotate = mat2(cos_factor, sin_factor, -sin_factor, cos_factor);
        vec2 uv = (v_uv - 0.5) * rotate + 0.5;
        uv = uv * 2 - 0.5;
 	    vec4 color = texture(loadingTexture, uv);
        outColor = mix(outColor, color, color.a); 
    } else
    {    
        outColor = vec4(texture(tileTexture, v_uv).rgb, 1.0);
    }
    */
    outColor = vec4(texture(tileTexture, v_uv).rgb, 1.0);
    //if (v_uv.x < 0.005 || v_uv.x > 0.995 || v_uv.y < 0.005 || v_uv.y > 0.995)
    //    outColor = vec4(0.4, 0.4, 0.4, 1.0);
}
