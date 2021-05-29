#include "Material/circlematerial.h"
#include <iostream>

using namespace std;

CircleMaterial::CircleMaterial():
    Material("Circle") {
    setColor("color", QVector4D(1.0, 0.0, 0.0, 1.0));
    setPointSize(10);
    setDisplayMode(GL_POINTS);
}


CircleMaterial::~CircleMaterial() {
}
