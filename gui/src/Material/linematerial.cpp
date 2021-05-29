#include "Material/linematerial.h"
#include <iostream>

using namespace std;

LineMaterial::LineMaterial():
    Material("Line") {
    setColor("color", QVector4D(1.0, 0.0, 0.0, 1.0));
    setLineWidth(4);
    setDisplayMode(GL_FILL);
}


LineMaterial::~LineMaterial() {
}
