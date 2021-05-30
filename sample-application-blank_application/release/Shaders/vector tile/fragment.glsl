#version 330
//VectorTile: Fragment 

in vec2 v_type;

uniform vec4 firstClass;
uniform vec4 secondClass;
uniform vec4 thirdClass;
uniform vec4 fourthClass;
uniform vec4 defaultColor;

out vec4 outColor;


void main( void )
{
    /*
    float a = v_type.x;
    if(a < 2.0) {
        outColor = firstClass;
    } else if(a < 3.0) {
        outColor = secondClass;
    } else if(a < 4.0) {
        outColor = thirdClass;
    } else if(a < 5.0) {
        outColor = fourthClass;
    } else {
        outColor = defaultColor;
    }
    */
    outColor = vec4(0, 0, v_type.x / 25000000.0, 1.0);
}
