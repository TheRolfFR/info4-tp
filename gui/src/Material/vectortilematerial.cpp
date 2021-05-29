#include "Material/vectortilematerial.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <ResourceManagement/texturemanager.h>
#include <ResourceManagement/tiletexturemanager.h>

using namespace std;

VectorTileMaterial::VectorTileMaterial():
    Material("VectorTileMaterial")
{
    srand (time(NULL));

    QVector4D first_class(1.0, 1.0, 1.0, 1.0);
    QVector4D second_class(1.0, 1.0, 0.0, 1.0);
    QVector4D third_class(1.0, 0.0, 1.0, 1.0);
    QVector4D fourth_class(1.0, 0.0, 0.0, 1.0);

    setColor("firstClass", first_class);
    setColor("secondClass", second_class);
    setColor("thirdClass", third_class);
    setColor("fourthClass", fourth_class);
    setColor("defaultColor", fourth_class);

    addUniform("highwaySize", 6);
    addUniform("waySize", 2);
    addUniform("defaultSize", 1);
    
    addUniform("u_type", 2);

    setPointSize(6);
    setLineWidth(4);
    
    setOption(GL_DEPTH_TEST, false);

    setDisplayMode(GL_LINE);
}


VectorTileMaterial::~VectorTileMaterial() {
    //cout << "VectorTileMaterial::~VectorTileMaterial() (" << name << ")" << endl;
}
