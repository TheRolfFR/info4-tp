#include "Material/rastertilematerial.h"
#include <iostream>

#include <ResourceManagement/shadermanager.h>
#include <ResourceManagement/texturemanager.h>
#include <ResourceManagement/tiletexturemanager.h>

using namespace std;

RasterTileMaterial::RasterTileMaterial(int x, int y, int z):
    Material("Raster tile")
{
    setColor("tileColor", QVector4D(116/255.0, 185/255.0, 1.0, 1.0));
    setTexture("tileTexture", TileTextureManager::getInstance()->importFromURL(x, y, z));
    
    setPointSize(6);
    setLineWidth(4);
    
    setOption(GL_DEPTH_TEST, false);

    setDisplayMode(GL_FILL);
}


RasterTileMaterial::~RasterTileMaterial() {
}
