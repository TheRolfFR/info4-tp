#include "Material/vehiclepositionmaterial.h"
#include <iostream>

#include <ResourceManagement/shadermanager.h>

using namespace std;

VehiclePositionMaterial::VehiclePositionMaterial():
    Material("Vehicle positions")
{
    setShader(ShaderManager::get("Vehicle positions"));
    setColor("color", QVector4D(1.0, 0.0, 0.0, 1.0));

    setPointSize(6);

    setDisplayMode(GL_POINT);
}


VehiclePositionMaterial::~VehiclePositionMaterial() {
}
