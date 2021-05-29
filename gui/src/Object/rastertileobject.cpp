#include <Object/rastertileobject.h>

#include <Material/rastertilematerial.h>
#include <Data/rastertiledata.h>

#include <Material/rastertilematerial.h>
#include <OpenGL/loadingmanager.h>

using std::cout;
using std::endl;

/**
 * \brief 	Default constructor of class RasterTileObject
 *
 * \param 	None
 * \return 	None
 */
RasterTileObject::RasterTileObject(View* view, int x, int y, int zoom): TileObject(view, "raster tile", x, y, zoom)
{
    m_material = std::make_shared<RasterTileMaterial>(x, y, zoom);
    m_data = std::make_shared<RasterTileData>(x, y, zoom);
    LoadingManager::getInstance()->load(m_data);
}


/**
 * \brief 	Default destructor of class RasterTileObject
 *
 * \param 	None
 * \return 	None
 */
RasterTileObject::~RasterTileObject(){
}
