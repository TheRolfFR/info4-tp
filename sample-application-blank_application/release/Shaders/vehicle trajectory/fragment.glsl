#version 330

in vec2 v_uv;

uniform vec4 diffuse;
uniform int u_width;
uniform int u_length;

out vec4 outColor;

int len;

void main( void )
{
 	outColor = diffuse;

    vec2 center = vec2(u_length / 2.0, u_width / 2.0);
    vec2 uv = vec2(v_uv.x * u_length, v_uv.y * u_width);
    uv -= center;
    float semi_center_length = (u_length - u_width) / 2.0;
    if(uv.x > semi_center_length) {
        vec2 uv_a = uv;
        vec2 uv_b = uv;
        uv_a.x -= semi_center_length; 
        if(length(uv_a) > u_width/2.0) {
            discard;
        }
    }
    if(uv.x < -semi_center_length) {
        vec2 uv_b = uv;
        uv_b.x += semi_center_length; 
        if(length(uv_b) > u_width/2.0) {
            discard;
        }
    }
}
