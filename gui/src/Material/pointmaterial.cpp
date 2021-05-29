#include "Material/pointmaterial.h"
#include <iostream>

#include <ResourceManagement/shadermanager.h>

using namespace std;

PointMaterial::PointMaterial():
    Material("Point")
{
    setShader(ShaderManager::getInstance()->get("point"));
    setColor("color", QVector4D(1.0, 0.0, 0.0, 1.0));

    setPointSize(6);

    setDisplayMode(GL_POINT);
}


PointMaterial::~PointMaterial() {
}
