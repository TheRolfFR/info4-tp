#version 330

in vec2 uv;

uniform vec4 color;
uniform int alert_sender;

out vec4 outColor;

void main( void )
{
    outColor = color; 
    if (length((uv - 0.5)/2) > 0.25)
        discard;
    if (alert_sender > 0) {
        if (length((uv - 0.5)/2) > 0.20) {
            outColor.x *= 1.8;
            outColor.y *= 1.8;
            outColor.z *= 1.8;
        } else {
            outColor.x *= 0.3;
            outColor.y *= 0.3;
            outColor.z *= 0.3;
        }
    }
}
